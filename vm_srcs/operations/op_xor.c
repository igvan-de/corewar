/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_xor.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 16:30:39 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/05 16:30:40 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	int		get_arg_1(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int				size;
	unsigned char	reg;
	int				rel_pos;
	short			t_ind;

	size = get_arg_size(cursor->op_code, get_bit(encode, 0), get_bit(encode, 1));
	if (size == 1)
	{
		reg = env->map[modi(cursor->position + 2)];
		return (cursor->registries[reg - 1]);
	}
	else if (size == 2)
	{
		t_ind = get_tind(env, cursor->position + 2);
		rel_pos = t_ind % IDX_MOD;
		return (get_tdir(env, cursor->position + rel_pos));
	}
	else if (size == 4)
		return (get_tdir(env, cursor->position + 2));
	error_exec(3);
	return (0);
}

static	int		get_arg_2(t_cursor *cursor, t_env *env, unsigned char encode, int size)
{
	int				arg_size;
	unsigned char	reg;
	int				rel_pos;
	short			t_ind;

	arg_size = get_arg_size(cursor->op_code, get_bit(encode, 2), get_bit(encode, 3));
	if (size == 1)
	{
		reg = env->map[modi(cursor->position + size + 2)];
		return (cursor->registries[reg - 1]);
	}
	else if (size == 2)
	{
		t_ind = get_tind(env, cursor->position + size + 2);
		rel_pos = t_ind % IDX_MOD;
		return (get_tdir(env, cursor->position + rel_pos));
	}
	else if (size == 4)
		return (get_tdir(env, cursor->position + size + 2));
	error_exec(3);
	return (0);
}

static	void	exec_xor(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int			arg_1;
	int			arg_2;
	int			arg_1_size;
	int			arg_2_size;
	unsigned	target_reg;

	arg_1 = get_arg_1(cursor, env, encode);
	arg_1_size = get_arg_size(cursor->op_code, get_bit(encode, 0), get_bit(encode, 1));
	arg_2 = get_arg_2(cursor, env, encode, arg_1_size);
	arg_2_size = get_arg_size(cursor->op_code, get_bit(encode, 2), get_bit(encode, 3));
	target_reg = env->map[modi(cursor->position + arg_1_size + arg_2_size + 2)];
	cursor->registries[target_reg - 1] = arg_1 ^ arg_2;
	set_carry(cursor, arg_1 ^ arg_2);
}

/*
**	op_xor executes the operation op_xor at the current
**	position of the cursor.
*/

void			op_xor(t_cursor *cursor, t_env *env)
{
	unsigned char op_code;
	unsigned char encode;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, encode, env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));
	exec_xor(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}