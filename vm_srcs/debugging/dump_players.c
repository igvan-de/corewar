/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_players.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	print contents of each player
**
**	@param players	:	list of players
**	@param env		:	global environment struct
**
**	dump_players is a debug function which can
**	print the contents of each player struct within
**	the players list with repeated calls to dump_champ_code.
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
