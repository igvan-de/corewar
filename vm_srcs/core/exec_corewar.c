/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_corewar.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 08:27:14 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:09:42 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	else if (cursor->op_code == 10)
		op_ldi(cursor, env);
	else if (cursor->op_code == 11)
		op_sti(cursor, env);
	else if (cursor->op_code == 12)
		op_fork(cursor, env);
	else if (cursor->op_code == 13)
		op_lld(cursor, env);
	else if (cursor->op_code == 14)
		op_lldi(cursor, env);
	else if (cursor->op_code == 15)
		op_lfork(cursor, env);
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
	if ((env->flag_byte & (1 << 1)) == (1 << 1) && env->dump_cycle == env->total_cycles)
		dump_mem(env);
	if ((env->flag_byte & (1 << 3)) == (1 << 3))
	{
		ft_putstr("It is now cycle ");
		ft_putnbr(env->total_cycles + 1);
		ft_putchar('\n');
	}
}

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
