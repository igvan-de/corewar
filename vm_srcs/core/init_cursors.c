/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_cursors.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 10:03:18 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:07:13 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief: get the starting position of the cursor
**
**	@param id				:	unique cursor/player id
**	@param env				:	global environment struct
**	@return unsigned int	:	starting position
**
**
**	get_position receives the cursor_id and iterates through the player_pos
**	map to find the first byte of the players execution code.
**	It returns the index of that address within the memory map.
*/

static	unsigned	int		get_position(unsigned id, t_env *env)
{
	unsigned i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if ((unsigned char)env->datamap[i].player == id)
		{
			env->datamap[i].cursor = 1;
			return (i);
		}
		i++;
	}
	error_init(2);
	return (0);
}

/*
**	@brief:	create a new cursor
**
**	@param env			: 	global environment struct
**	@return t_cursor*	:	new cursor
**
**	new_cursor is used in init_cursors to create a new
**	cursor for each active player.
*/

static	t_cursor			*new_cursor(t_env *env, int player_nbr)
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
	new->registries[0] = -1 * player_nbr;
	new->carry = 0;
	new->jump = 0;
	new->last_live = 0;
	new->live_counter = 0;
	new->position = get_position(new->id, env);
	new->op_code = 0;
	new->wait_cycles = 0;
	return (new);
}

void						init_cursors(t_env *env)
{
	unsigned	i;
	t_cursor	*new;
	t_player	*curr;
	t_list		*iter;

	i = 0;
	iter = env->players;
	while (i < env->total_players)
	{
		curr = iter->content;
		new = new_cursor(env, curr->nbr);
		push_cursor(new, &env->cursor_stack);
		new = NULL;
		i++;
	}
}
