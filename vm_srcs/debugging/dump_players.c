/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_players.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 08:18:18 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/25 08:18:18 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	dump_players takes a ptr to a list of players and
**	prints the header and execution code of each player
**	using dump_champ_code.
*/

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
