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

	player_nb++;
	mem_per_player = MEM_SIZE / env->players;
	load_index = mem_per_player * (player_nb - 1);
	return (load_index);
}

static	void	load_player(t_env *env, int player_nb)
{
	int				load_index;
	unsigned		i;
	t_player		*curr_player;
	unsigned int	size;

	curr_player = env->player;
	load_index = get_load_index(player_nb, env);
	i = 0;
	size = rev_endian(curr_player->header->prog_size);
	while (i < size)
	{
		env->map[load_index] = curr_player->exec_code[i];
		i++;
		load_index++;
	}
}

void	load_players(t_env *env)
{
	int i;

	i = 0;
	while (i < env->players)
	{
		load_player(env, i);
		i++;
	}
}