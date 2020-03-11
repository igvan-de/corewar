/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intro_players.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 12:19:30 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:12:13 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	print player intro message
**
**	@param player : target player
*/

static	void	intro_player(t_player *player)
{
	ft_putstr("* Player ");
	ft_putnbr(player->nbr);
	ft_putstr(", weighing ");
	ft_putnbr(rev_endian(player->header->prog_size));
	ft_putstr(" bytes, \"");
	ft_putstr(player->header->prog_name);
	ft_putstr("\" (\"");
	ft_putstr(player->header->comment);
	ft_putendl("\") !");
}

void			intro_players(t_env *env)
{
	t_list *iter;

	ft_putendl("Introducing contestants...");
	iter = env->players;
	while (iter)
	{
		intro_player(iter->content);
		iter = iter->next;
	}
}
