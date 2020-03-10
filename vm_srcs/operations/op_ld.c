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

static	void	exec_ld(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int arg_1;
	int arg_2;

	arg_1 = get_arg(cursor, env, encode, 1);
	arg_2 = get_reg_num(cursor, env, encode, 2);
	cursor->registries[arg_2 - 1] = arg_1;
	set_carry(cursor, arg_1);
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

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, encode, env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));
	exec_ld(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}
