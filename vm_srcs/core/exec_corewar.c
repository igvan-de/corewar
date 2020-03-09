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
	else if (cursor->op_code == 11)
		op_sti(cursor, env);
	else if (cursor->op_code == 12)
		op_fork(cursor, env);
	else if (cursor->op_code == 15)
		op_lfork(cursor, env);
	else if (cursor->op_code < 1 || 16 < cursor->op_code)
	{
		cursor->position = modi(cursor->position + 1);
		cursor->op_code = 0;
	}
	else
		invalid_op(cursor, env, 1);
}

/*
**	set_opcode receives a cursor and loads the op_code
**	stored at the current position into the cursor->op_code
**	variable. The associated wait_cycles of the operation
**	is also retrieved from the op_tab.
*/

static	void	set_opcode(t_cursor *cursor, t_env *env)
{
	cursor->op_code = env->map[modi(cursor->position)];
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
	if (env->total_cycles == 0 || cursor->wait_cycles == 0)
	{
		if (1 <= env->map[modi(cursor->position)] && env->map[modi(cursor->position)] <= 16)
			set_opcode(cursor, env);
		else
		{
			cursor->op_code = env->map[modi(cursor->position)];
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
**	check_flags parses the flag byte and executes
**	verbosity dumps or the visualizer depending on
**	which flags are turned on.
*/

static	void	check_flags(t_env *env)
{
	if ((env->flag_byte & 1) == 1)
		print_map(env);
	if ((env->flag_byte & (1 << 1)) == (1 << 1) && env->dump_cycle == env->total_cycles)
		dump_mem(env);
	if ((env->flag_byte & (1 << 3)) == (1 << 3))
	{
		ft_putstr("It is now cycle ");
		ft_putnbr(env->total_cycles + 1);
		ft_putchar('\n');
	}
}

/*
**	exec_corewar executes the main program with
**	the information stored in the global environment struct.
**
**	only runs with ops: zjmp / live/ sti / ld.
*/

void			exec_corewar(t_env *env)
{
	if ((env->flag_byte & 1) == 1)
		init_ncurses(env);
	if (env->cycles_to_die <= 0)
		return ;
	if (env->total_cursors == 0)
		return ;
	while (env->cycles < env->cycles_to_die)
	{
		check_flags(env);
		exec_cursor_stack(env);
		if (env->cycles_to_die < 1)
			check_corewar(env);
		(env->cycles)++;
		(env->total_cycles)++;
	}
	if (env->cycles_to_die > 0)
		check_corewar(env);
	exec_corewar(env);
}
