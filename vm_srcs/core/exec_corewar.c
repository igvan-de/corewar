/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_corewar.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief: set the operation code within the cursor
**
**	@param cursor	: target cursor
**	@param env		: global environment struct
**
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
**	@brief:	evaluate cursor state and process the cursor
**
**	@param cursor 	:	target cursor
**	@param env 		:	global environment structure
**
**	exec_cursors can perform different actions depending on the
**	current state of the cursor.
**
**	-> if it is the very first cycle or if the wait_cycles of this
**		cursor is 0, the cursor reads a byte from the map at
**		its current position. If it is a valid operation code,
**		the cursors' wait_cycles gets adjusted to match the operation.
**
**	->	afterwards, if the wait_cycles of the cursor is higher than 1,
**		the wait_cycles gets decremented by one.
**
**	->	afterwards, if wait_cycles is zero, the cursor tries to execute
**		operation stored in the cursor.
**
**	note:	the function is designed in this way so that multiple actions
**			can happen consecutively in the same cycle. A cursor can read
**			an instruction, decrement its wait_cycle and immediately execute
**			that operation in one cycle.
*/

static	void	exec_cursor(t_cursor *cursor, t_env *env)
{
	if (env->total_cycles == 0 || cursor->wait_cycles == 0)
	{
		if (1 <= env->map[modi(cursor->position)] &&
			env->map[modi(cursor->position)] <= 16)
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
**	@brief:	iterate through the cursor stack and call exec_cursor
**
**	@param env	:	global environment struct
**
**	During each cycle, every cursor in the cursor stack needs to be
**	processed with exec_cursor. Exec_cursor_stack iterates through
**	the entire cursor stack and calls exec_cursor for each cursor
**	in the stack.
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
**	@brief:	parse the flag byte and call related actions
**
**	@param env:	global environment structure.
**
**	check_flags checks which bits in env->flag_byte are turned
**	on, and performs an action if a flag is turned on.
**
**	->	if the '-visual' flag is on, the function prints the game
**		state each cycle using print_map.
**
**	->	if the '-dump' flag is on and the dump_cycle is equal to the
**		current cycle, the function prints the memory map
**		to stdout and exits the game.
**
**	->	if the '-v' flag is turned on with option 2 or 18, the current
**		cycle is printed to stdout.
*/

static	void	check_flags(t_env *env)
{
	if ((env->flag_byte & 1) == 1)
		print_map(env);
	if ((env->flag_byte & (1 << 6)) == (1 << 6) &&
		env->dump_cycle == env->total_cycles)
		dump_mem_alt(env);
	if ((env->flag_byte & (1 << 1)) == (1 << 1) &&
		env->dump_cycle == env->total_cycles)
		dump_mem(env);
	if ((env->flag_byte & (1 << 3)) == (1 << 3))
	{
		ft_putstr("It is now cycle ");
		ft_putnbr(env->total_cycles + 1);
		ft_putchar('\n');
	}
}

/*
**	@brief:	run the main corewar process
**
**	@param env	:	global environment structure
**
**	exec_corewar runs the programs main process. The process continues
**	as long as there are active cursors in the cursor stack and
**	env->cycles_to_die is higher or equal to zero. The main process
**	consists of several parts:
**
**	->	check which flags are enabled in check_flags.
**	->	process each cursor in exec_cursor_stack.
**	->	if CYCLE_TO_DIE is 0, run a check each cycle. The check is described
**		in check_corewar.c
**
**	once CYCLE_TO_DIE cycles have been processed, the current iteration ends
**	and a check occurs in check_corewar. Afterwards, exec_corewar gets
**	called recursively for the next iteration.
**
**	note: 	Over the course of the game, CYCLE_TO_DIE will continue to get
**			smaller, which gives cursors less time to send a live signal.
**
**	the last player to send a valid live signal wins the game.
*/

void			exec_corewar(t_env *env)
{
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
