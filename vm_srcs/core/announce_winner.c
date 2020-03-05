/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   announce_winner.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 13:04:54 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/04 13:04:55 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	char	*player_name(t_env *env, int id)
{
	t_list		*iter;
	t_player	*curr;

	iter = env->players;
	while (iter)
	{
		curr = iter->content;
		if (curr->nbr == id)
			return (curr->header->prog_name);
		iter = iter->next;
	}
	return ("NULL");
}

void			announce_winner(t_env *env)
{
	ft_putstr("Contestant ");
	ft_putnbr(env->player_last_alive);
	ft_putstr(", \"");
	ft_putstr(player_name(env, env->player_last_alive));
	ft_putstr("\", has won !\n");
}
