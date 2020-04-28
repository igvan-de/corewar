/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_op.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	exec_basic_op(t_cursor *cursor, t_env *env)
{
	if (cursor->op_code == 1)
		op_live(cursor, env);
	else if (cursor->op_code == 2)
		op_ld(cursor, env);
	else if (cursor->op_code == 3)
		op_st(cursor, env);
	else if (cursor->op_code == 4)
		op_add(cursor, env);
	else if (cursor->op_code == 5)
		op_sub(cursor, env);
	else if (cursor->op_code == 6)
		op_and(cursor, env);
	else if (cursor->op_code == 7)
		op_or(cursor, env);
	else if (cursor->op_code == 8)
		op_xor(cursor, env);
	else if (cursor->op_code == 9)
		op_zjmp(cursor, env);
	else if (cursor->op_code == 10)
		op_ldi(cursor, env);
}

static	void	exec_big_op(t_cursor *cursor, t_env *env)
{
	if (cursor->op_code == 11)
		op_sti(cursor, env);
	else if (cursor->op_code == 12)
		op_fork(cursor, env);
	else if (cursor->op_code == 13)
		op_lld(cursor, env);
	else if (cursor->op_code == 14)
		op_lldi(cursor, env);
	else if (cursor->op_code == 15)
		op_lfork(cursor, env);
	else if (cursor->op_code == 16)
		op_aff(cursor, env);
}

/*
**	@brief:	attempt to execute the operation in the cursor
**
**	@param cursor	:	target cursor
**	@param env		:	global environment struct
**
**	once a cursors' wait_cycles has reached 0, the cursor
**	will attempt to execute the operation by calling exec_op.
**	if the value stored in cursor->op_code is a valid operation code,
**	exec_op calls the operation function related to that code.
**	otherwise, the operation code is invalid and the cursor jumps
**	to the next operation within the memory map.
*/

void			exec_op(t_cursor *cursor, t_env *env)
{
	if (1 <= cursor->op_code && cursor->op_code <= 10)
		exec_basic_op(cursor, env);
	else if (11 <= cursor->op_code && cursor->op_code <= 16)
		exec_big_op(cursor, env);
	else if (cursor->op_code < 1 || 16 < cursor->op_code)
	{
		env->datamap[cursor->position].cursor = 0;
		cursor->position = modi(cursor->position + 1);
		env->datamap[cursor->position].cursor = 1;
		cursor->op_code = 0;
	}
	else
		invalid_op(cursor, env, 1);
}
