/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_corewar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 11:59:22 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:11:12 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/**
**	@brief: print current CYCLES_TO_DIE to stdout
**
**	@param cycles_to_die : current value of CYCLES_TO_DIE
**
**	dump_ctd prints the current CYCLE_TO_DIE value if
**	the verbosity flag is enabled and verbosity is 16 or 18.
*/

static	void	dump_ctd(int cycles_to_die)
{
	ft_putstr("Cycle to die is now ");
	ft_putnbr(cycles_to_die);
	ft_putchar('\n');
}

/**
**	@brief:	determine if a cursor is dead
**
**	@param cursor	: 	target cursor
**	@param env		: 	global environment structure
**	@return int		:	true (1) or false (0)
**
**
**	is_dead checks if a cursor is dead or alive.
**	A cursor is considered dead if:
**
**	-> 	it performed operation live more than CYCLES_TO_DIE
**
**	->	it performed its last live operation more than CYCLES_TO_DIE cycles
**		ago.
*/

static	int		is_dead(t_cursor *cursor, t_env *env)
{
	if (cursor->live_counter >= env->cycles_to_die)
		return (1);
	else if (cursor->last_live <= (env->total_cycles - env->cycles_to_die))
		return (1);
	return (0);
}

/**
**	@brief:	free a cursor and remove it from the cursor stack
**
**	@param cursor			:	cursor to be removed
**	@param cursor_stack 	:	cursor stack
**
**	delete_cursor frees the cursor passed as paremeter and
**	reconnects the neighboring cursors in the cursor stack using
**	the next and prev pointers.
*/

static	void	delete_cursor(t_cursor *cursor, t_cursor **cursor_stack)
{
	if (cursor->prev != NULL)
		(cursor->prev)->next = cursor->next;
	else
		*cursor_stack = cursor->next;
	if (cursor->next != NULL)
		(cursor->next)->prev = cursor->prev;
	free(cursor->registries);
	free(cursor);
}

/*
**	@brief:	remove dead cursors from the cursor stack
**
**	@param env	:	global environment struct
**
**	parse_cursor_stack iterates through the cursor_stack
**	and, if a cursor is dead, it is freed and removed from the stack.
*/

static	void	parse_cursor_stack(t_env *env)
{
	t_cursor *iter;

	iter = env->cursor_stack;
	while (iter)
	{
		if (is_dead(iter, env) == 1 || env->cycles_to_die <= 0)
		{
			env->datamap[iter->position].cursor = 0;
			delete_cursor(iter, &env->cursor_stack);
			iter = env->cursor_stack;
			env->total_cursors--;
			if (iter == NULL)
				return ;
			else
				continue ;
		}
		iter = iter->next;
	}
}

void			check_corewar(t_env *env)
{
	env->checks_counter++;
	env->cycle_last_check = env->total_cycles;
	if (env->live_counter >= NBR_LIVE)
	{
		env->cycles_to_die -= CYCLE_DELTA;
		if ((env->flag_byte & (1 << 3)) == (1 << 3))
			dump_ctd(env->cycles_to_die);
	}
	else if (env->live_counter < NBR_LIVE)
	{
		if (env->checks_counter >= MAX_CHECKS)
		{
			env->cycles_to_die -= CYCLE_DELTA;
			if ((env->flag_byte & (1 << 3)) == (1 << 3))
				dump_ctd(env->cycles_to_die);
			env->checks_counter = 0;
		}
	}
	parse_cursor_stack(env);
	env->live_counter = 0;
	env->cycles = 0;
}
