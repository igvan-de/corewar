/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_corewar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 11:59:22 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/28 11:59:23 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	is_dead checks if a cursor is dead.
*/

static	int		is_dead(t_cursor *cursor, t_env *env)
{
	if (cursor->live_counter == 0)
		return (1);
	if (cursor->live_counter > env->cycles_to_die)
		return (1);
	else if (cursor->last_live < env->total_cycles - env->cycles_to_die)
		return (1);
	return (0);
}

/*
**	delete_cursor frees a dead cursor and reconnects the
**	neighboring cursors in the cursor_stack.
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
**	parse_cursor_stack iterates through the cursor_stack
**	and if a cursor is dead, it is deleted.
*/

static	void	parse_cursor_stack(t_env *env)
{
	t_cursor *iter;

	iter = env->cursor_stack;
	while (iter)
	{
		if (is_dead(iter, env) == 1 || env->cycles_to_die <= 0)
		{
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

/*
**	reset_cursor_lives iterates through the cursor_stack and
**	sets the live_counter for each cursor to 0.
*/

static	void	reset_cursor_lives(t_cursor *cursor_stack)
{
	t_cursor *iter;

	iter = cursor_stack;
	while (iter)
	{
		iter->live_counter = 0;
		iter = iter->next;
	}
}

/*
**	check_corewar runs a checkup each CYCLE_TO_DIE cycles.
**
**	if during the last CTD cycles, more than NBR_LIVE live operations
**	were performed, CTD gets decreased by CYCLE_DELTA.
**
**	else if more than MAX_CHECKS checks were performed,
**	CTD gets decreased by CYCLE_DELTA.
**
**	dead cursors are removed from the cursor stack.
**	live counter for each cursor is reset.
*/

void			check_corewar(t_env *env)
{
	env->checks_counter++;
	env->cycle_last_check = env->total_cycles;
	parse_cursor_stack(env);
	if (env->live_counter >= NBR_LIVE)
		env->cycles_to_die -= CYCLE_DELTA;
	else if (env->live_counter < NBR_LIVE)
	{
		if (env->checks_counter >= MAX_CHECKS)
		{
			env->cycles_to_die -= CYCLE_DELTA;
			env->checks_counter = 0;
		}
	}
	env->live_counter = 0;
	env->cycles = 0;
	reset_cursor_lives(env->cursor_stack);
}
