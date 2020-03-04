/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_sti.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 11:04:59 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 11:04:59 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	retrieve the bytes of the second argument.
*/

static	short	get_arg_2(unsigned char encode, t_cursor *c, t_env *env)
{
	unsigned char arg_size;

	arg_size = get_arg_size(c->op_code, get_bit(encode, 2), get_bit(encode, 3));
	if (arg_size == 1)
		return((short)env->map[modi(c->position + 3)]);
	else if (arg_size == 2)
		return ((short)to_2bytes(env->map[modi(c->position + 3)], env->map[modi(c->position + 4)]));
	error_exec(3);
	return (0);
}

/*
**	retrieve the bytes of the third argument
*/

static	short	get_arg_3(unsigned char encode, t_cursor *c, t_env *env)
{
	unsigned char arg_size_3;
	unsigned char arg_size_2;

	arg_size_2 = get_arg_size(c->op_code, get_bit(encode, 2), get_bit(encode, 3));
	arg_size_3 = get_arg_size(c->op_code, get_bit(encode, 4), get_bit(encode, 5));
	if (arg_size_3 == 1)
		return((short)env->map[modi(c->position + arg_size_2 + 3)]);
	else if (arg_size_3 == 2)
		return ((short)to_2bytes(env->map[modi(c->position + arg_size_2 + 3)], env->map[modi(c->position + arg_size_2 + 4)]));
	error_exec(3);
	return (0);
}

/*
**	exec_sti retrieves the needed values from the memory map
**	in relation to the current position of the cursor, and executes
**	the sti operation with the values found.
*/

static	void	exec_sti(t_cursor *c, t_env *env, unsigned char encode, unsigned char reg_num)
{
	short			arg_2;
	short			arg_3;
	int				target_val;
	int				rel_pos;

	arg_2 = get_arg_2(encode, c, env);
	arg_3 = get_arg_3(encode, c, env);
	target_val = c->registries[reg_num - 1];
	rel_pos = (arg_2 + arg_3) % IDX_MOD;
	write_bytes(target_val, env, c, rel_pos);
	env->player_pos[modi(c->position + rel_pos)] = c->registries[0] * -1;
	env->player_pos[modi(c->position + rel_pos + 1)] = c->registries[0] * -1;
	env->player_pos[modi(c->position + rel_pos + 2)] = c->registries[0] * -1;
	env->player_pos[modi(c->position + rel_pos + 3)] = c->registries[0] * -1;
}

/*
**	op_sti executes the operation sti at the current position
**	of the cursor passed as parameter. It receives a register number
**	as first argument, and writes the value stored in that register
**	to the relative address calculated as a result of:
**
**	cursor->position + (SECOND_ARGUMENT + THIRD_ARGUMENT % IDX_MOD);
**
**	if the encoding byte or the register numbers are invalid, the function
**	moves the cursor to the next operation by calling move_cursor.
*/

void			op_sti(t_cursor *cursor, t_env *env)
{
	unsigned char	op_code;
	unsigned char	encode;
	unsigned char	reg_num;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, env->map[modi(cursor->position + 1)], env) == 0)
		return (invalid_op(cursor, env));
	reg_num = env->map[modi(cursor->position + 2)];
	if (reg_num < 1 || 16 < reg_num)
		return (invalid_op(cursor, env));
	exec_sti(cursor, env, encode, reg_num);
	move_cursor_encode(cursor, env, encode, op_code);
}
