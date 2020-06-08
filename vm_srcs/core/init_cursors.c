/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_cursors.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	int			verif_position(int position, t_cursor *new, t_env *env)
{
	if (position == -1)
	{
		(env->total_cursors)--;
		free(new->registries);
		free(new);
		return (0);
	}
	return (1);
}

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

static	int			get_position(unsigned id, t_env *env)
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
	return (-1);
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

static	t_cursor	*new_cursor(t_env *env, int player_nbr)
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
	new->registries[1] = -1 * player_nbr;
	new->carry = 0;
	new->jump = 0;
	new->last_live = 0;
	new->live_counter = 0;
	new->position = get_position(new->id, env);
	if (verif_position(new->position, new, env) == 0)
		return (NULL);
	new->op_code = 0;
	new->wait_cycles = 0;
	return (new);
}

/*
**	@brief:	initialize the cursor stack
**
**	@param env	:	global environment struct
**
**	init_cursors sets up the initial cursor_stack variable of env, at
**	the beginning of the program.
**	For each active player, a new cursor is created with a position
**	pointing to the first byte of the execution code.
*/

void				init_cursors(t_env *env)
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
		if (new != NULL)
			push_cursor(new, &env->cursor_stack);
		new = NULL;
		iter = iter->next;
		i++;
	}
}
