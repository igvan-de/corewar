/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_corewar.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 08:27:14 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 08:27:15 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	exec_op(t_cursor *cursor, t_env *env)
{
	if (cursor->op_code == 1)
		op_live(cursor, env);
	else if (cursor->op_code == 2)
		op_ld(cursor, env);
	else if (cursor->op_code == 3)
		op_add(cursor, env);
	else if (cursor->op_code == 4)
		op_sub(cursor, env);
	else if (cursor->op_code == 9)
		op_zjmp(cursor, env);
	else if (cursor->op_code == 11)
		op_sti(cursor, env);
	else
		op_invalid(cursor, env);
}

static	void	set_opcode(t_cursor *cursor, t_env *env)
{
	cursor->op_code = *(cursor->position);
	cursor->wait_cycles = env->op_tab[cursor->op_code].cycles;
}

static	void	exec_cursor(t_cursor *cursor, t_env *env)
{
	if (env->cycles == 0 || cursor->wait_cycles == 0)
	{
		if (1 <= *(cursor->position) && *(cursor->position) <= 16)
			set_opcode(cursor, env);
		else
		{
			cursor->op_code = *(cursor->position);
			cursor->wait_cycles = 0;
		}
	}
	if (cursor->wait_cycles >= 1)
		(cursor->wait_cycles)--;
	if (cursor->wait_cycles == 0)
		exec_op(cursor, env);
}

static	void	exec_cursor_stack(t_env *env)
{
	t_cursor *iter;

	iter = env->cursor_stack;
	while (iter)
	{
		exec_cursor(iter, env);
		iter = iter->next;
	}
}

static	void	exec_corewar(t_env *env)
{
	if (env->cycles_to_die <= 0)
		return ;
	while (env->cycles < env->cycles_to_die)
	{
		exec_cursor_stack(env);
		(env->cycles)++;
	}
	exec_check(env);
	exec_corewar(env);
}
