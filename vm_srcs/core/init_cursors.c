/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_cursors.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 10:03:18 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/25 10:03:19 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	get_position receives the cursor_id and loops through the player_pos
**	map to find the first byte of the players execution code.
**	It returns the index of that address within the memory map.
*/

static	unsigned	int		get_position(unsigned id, t_env *env)
{
	unsigned i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if ((unsigned char)env->player_pos[i] == id)
			return (i);
		i++;
	}
	error_init(2);
	return (0);
}

/*
**	new_cursor is used in init_cursors to create a new
**	cursor for each active player.
*/

static	t_cursor			*new_cursor(t_env *env)
{
	t_cursor	*new;

	new = (t_cursor *)malloc(sizeof(t_cursor));
	if (!new)
		error_mem();
	(env->total_cursors)++;
	new->id = env->total_cursors;
	new->prev = NULL;
	new->next = NULL;
	new->registries = init_registries();
	new->registries[0] = -1 * new->id;
	new->carry = 0;
	new->jump = 0;
	new->last_live = 0;
	new->live_counter = 0;
	new->position = get_position(new->id, env);
	new->op_code = 0;
	new->wait_cycles = 0;
	return (new);
}

/*
**	init_cursors sets up the initial cursor_stack variable of env, at
**	the beginning of the program.
**	For each active player, a new cursor is created with a position
**	pointing to the first byte of the execution code.
*/

void						init_cursors(t_env *env)
{
	unsigned	i;
	t_cursor	*new;

	i = 0;
	while (i < env->total_players)
	{
		new = new_cursor(env);
		push_cursor(new, &env->cursor_stack);
		new = NULL;
		i++;
	}
}
