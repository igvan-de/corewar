/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_players.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	int			get_last_nbr(t_list *players)
{
	t_list		*iter;
	t_player	*curr;

	iter = players;
	while (iter)
	{
		curr = iter->content;
		iter = iter->next;
	}
	return (curr->nbr);
}

/*
**	@brief: determine player location
**
**	@param env			:	global environment struct
**	@param player_nb	:	player number
**
**	get_load_index receives a player number and calculates the starting
**	position of this player in memory. It returns the index of the starting
**	byte of the players' target position.
*/

static	int			get_load_index(int player_nb, t_env *env)
{
	int mem_per_player;
	int	load_index;

	mem_per_player = MEM_SIZE / env->total_players;
	load_index = mem_per_player * (player_nb - 1);
	return (load_index);
}

/*
**	@brief: retrieve a pointer to target player
**
**	@param env			:	global environment struct
**	@param player_nbr	:	target player number
**
**	get_player receives a player number and retrieves a ptr
**	to that player from the env->players list. If the number is not found,
**	the function produces an error.
*/

static	t_player	*get_player(int player_nbr, t_env *env)
{
	t_list		*iter;
	t_player	*curr;
	int			i;

	i = 1;
	iter = env->players;
	while (iter)
	{
		curr = iter->content;
		if (i == player_nbr)
			return (curr);
		iter = iter->next;
		i++;
	}
	error_init(1);
	return (NULL);
}

/*
**	@brief: load a player into memory
**
**	@param env			:	global environment struct
**	@param player_nb	:	player number
**
**	load_player receives the number of the player to be loaded into memory.
**	It then loads the source code of this player into memory at env->map and
**	stores the player number at env->datamap. After the source code has been
**	copied into memory, the initial source code version in the players list
**	is freed.
*/

static	void		load_player(t_env *env, int player_nb)
{
	unsigned		i;
	unsigned int	size;
	int				load_index;
	t_player		*curr_player;

	curr_player = get_player(player_nb, env);
	load_index = get_load_index(player_nb, env);
	i = 0;
	size = rev_endian(curr_player->header->prog_size);
	while (i < size)
	{
		env->map[load_index] = curr_player->exec_code[i];
		env->datamap[load_index].player = player_nb;
		i++;
		load_index++;
	}
	free(curr_player->exec_code);
	curr_player->exec_code = NULL;
}

/*
**	@brief: load saved players into the memory map
**
**	@param env	: global environment struct
**
**	load_players receives the list of players in env->players
**	and loads their source code into memory at env->map.
*/

void				load_players(t_env *env)
{
	unsigned	i;

	i = 0;
	while (i < env->total_players)
	{
		load_player(env, i + 1);
		i++;
	}
	env->player_last_alive = get_last_nbr(env->players);
}
