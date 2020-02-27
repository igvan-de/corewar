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

/*
**	op_invalid is the exit routine for finding invalid operations.
*/

static	void	op_invalid(t_cursor *cursor, t_env *env)
{
	printf("	operation code %i is not recognized at cursor: %i\n", *(cursor->position), cursor->id);
	if (!env)
		exit(0);
	exit(0);
}

/*
**	exec_op executes the operation stored in the cursor
**	passed as parameter. if the op_code is not recognized
**	it calls op_invalid.
*/

static	void	exec_op(t_cursor *cursor, t_env *env)
{
	if (cursor->op_code == 1)
		op_live(cursor, env);
	else if (cursor->op_code == 2)
		op_ld(cursor, env);
	else if (cursor->op_code == 9)
		op_zjmp(cursor);
	else if (cursor->op_code == 11)
		op_sti(cursor, env);
	else
		op_invalid(cursor, env);
}

/*
**	set_opcode receives a cursor and loads the op_code
**	stored at the current position into the cursor->op_code
**	variable. The associated wait_cycles of the operation
**	is also retrieved from the op_tab.
*/

static	void	set_opcode(t_cursor *cursor, t_env *env)
{
	cursor->op_code = *(cursor->position);
	cursor->wait_cycles = env->op_tab[cursor->op_code].cycles;
}

/*
**	exec_cursor receives a cursor and performs actions
**	based on the state of the cursor and the environment.
**
**	if it is the first cycle or if the wait_cycles of
**	the cursor is 0,  exec_cursor loads the operation
**	at the current position of the cursor.
**
**	if wait_cycles is higher than 0, wait_cycles is decremented.
**	if wait_cycles is 0, it executes the operation stored at
**	the current position.
*/

static	void	exec_cursor(t_cursor *cursor, t_env *env)
{
	if (env->cycles == 0 || cursor->wait_cycles == 0)
	{
		if (1 <= *(cursor->position) && *(cursor->position) <= 16)
			set_opcode(cursor, env);
		else
		{
			printf("	op_code is invalid!\n");
			cursor->op_code = *(cursor->position);
			cursor->wait_cycles = 0;
		}
	}
	if (cursor->wait_cycles >= 1)
		(cursor->wait_cycles)--;
	if (cursor->wait_cycles == 0)
		exec_op(cursor, env);
}

/*
**	exec_cursor iterates through the cursor_stack
**	and calls exec_cursor for each cursor in the stack.
*/

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

/*
**	exec_corewar executes the main program with
**	the information stored in the global environment struct.
**
**	UNDER CONSTRUCTION --> only runs up to 1536 cycles with ops: zjmp / live/ sti / ld.
*/

void			exec_corewar(t_env *env)
{
	if ((env->flag_byte & 1) == 1)
		init_ncurses(env);
	if (env->cycles_to_die <= 0)
		return ;
	while (env->cycles < env->cycles_to_die)
	{
		exec_cursor_stack(env);
		(env->cycles)++;
		if ((env->flag_byte & 1) == 1)
			print_map(env);
	}
}
