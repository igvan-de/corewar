/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_players.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 14:13:19 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:08:12 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	get_load_index takes a player number and calculates the
**	starting position of that player within the memory area at
**	env->map.
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
**	get_player takes a ptr to the main environment struct
**	and a player number. It returns a ptr to the player with
**	that number within the env->players list.
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
**	load_players takes a ptr to the main environment struct and
**	loads the players stored in the list env->players into the
**	allocated memory area at env->map.
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
	env->player_last_alive = env->total_players;
}
