/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_players.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 08:18:18 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 17:20:26 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	dump_players(t_list *players, t_env *env)
{
	t_list *iter;

	iter = players;
	while (iter)
	{
		dump_champ_code((t_player *)iter->content, env);
		iter = iter->next;
	}
}
