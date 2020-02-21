/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_players.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 14:13:19 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/21 14:13:20 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	int	get_load_index(int player_nb, t_env *env)
{
	int mem_per_player;
	int	load_index;

	mem_per_player = MEM_SIZE / env->total_players;
	load_index = mem_per_player * (player_nb - 1);
	return (load_index);
}

static	t_player	*get_player(int player_nbr, t_env *env)
{
	t_list		*iter;
	t_player	*curr;

	iter = env->players;
	while (iter)
	{
		curr = iter->content;
		if (curr->nbr == player_nbr)
			return (curr);
		iter = iter->next;
	}
	error_init(1);
	return (NULL);
}

static	void	load_player(t_env *env, int player_nb)
{
	int				load_index;
	unsigned		i;
	t_player		*curr_player;
	unsigned int	size;

	curr_player = get_player(player_nb, env);
	load_index = get_load_index(player_nb, env);
	i = 0;
	size = rev_endian(curr_player->header->prog_size);
	while (i < size)
	{
		env->map[load_index] = curr_player->exec_code[i];
		env->player_pos[load_index] = player_nb;
		i++;
		load_index++;
	}
}

void	load_players(t_env *env)
{
	int i;

	i = 0;
	while (i < env->total_players)
	{
		load_player(env, i + 1);
		i++;
	}
}