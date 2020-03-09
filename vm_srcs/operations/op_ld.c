/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_ld.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 16:18:53 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 16:18:54 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	exec_ld executes the ld operation at the current position of the cursor.
**	behavior differs based on the first argument --> look below for details.
*/

static	void	exec_ld(t_cursor *cursor, unsigned char arg_1_size, unsigned char reg_num, t_env *env)
{
	int		t_dir_value;
	short	t_ind_value;
	int		type_flag;
	int		rel_pos;

	type_flag = 0;
	if (arg_1_size == 4)
	{
		type_flag = 1;
		t_dir_value = get_tdir(cursor->op_code, env, cursor->position + 2);
	}
	else if (arg_1_size == 2)
	{
		type_flag = 0;
		t_ind_value = get_tind(env, cursor->position + 2);
	}
	if (type_flag == 0)
	{
		rel_pos = t_ind_value % IDX_MOD;
		t_dir_value = get_tdir(cursor->op_code, env, cursor->position + rel_pos);
	}
	cursor->registries[reg_num - 1] = t_dir_value;
	set_carry(cursor, t_dir_value);
}

/*
**	op_ld executes the operation ld at the current position of the cursor.
**	if the first argument is a T_DIR, the value stored within this T_DIR
**	is written into the cursor registry at the number stored as the second
**	argument T_REG.
**
**	Otherwise, if the first argument is a T_IND, it represents a relative address.
**	It then reads the value stored at the address calculated by:
**
**	cursor->position + (FIRST_ARGUMENT % IDX_MOD);
**
**	and writes this value into cursor registry with the number stored as the second
**	argument T_REG.
**
**	If the value written is 0, the carry flag in the cursor is set to 1. Otherwise,
**	if the value written is !0, the carry flag is set to 0.
*/

void			op_ld(t_cursor *cursor, t_env *env)
{
	unsigned char	op_code;
	unsigned char	encode;
	unsigned char	arg_size_1;
	unsigned char	reg_num;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, encode, env) == 0)
		return (invalid_op(cursor, env, 1));
	arg_size_1 = get_arg_size(cursor->op_code, get_bit(encode, 0), get_bit(encode, 1));
	reg_num = env->map[modi(cursor->position + arg_size_1 + 2)];
	if (reg_num < 1 || 16 < reg_num)
		return (invalid_op(cursor, env, 2));
	exec_ld(cursor, arg_size_1, reg_num, env);
	move_cursor_encode(cursor, env, encode, op_code);
}
