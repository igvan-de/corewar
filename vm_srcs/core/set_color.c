/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_color.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 07:39:55 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/25 07:39:56 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	set_color takes a ptr to an allocated player, and
**	sets its color variable according to the given player number.
**	If the player is not allocated, the functions segfaults, if
**	the player number is not in range of 1-6, it returns error.
*/

void	set_color(t_player *player)
{
	if (player->nbr == 1)
		player->color = ft_strdup(ANSI_COLOR_RED);
	else if (player->nbr == 2)
		player->color = ft_strdup(ANSI_COLOR_GREEN);
	else if (player->nbr == 3)
		player->color = ft_strdup(ANSI_COLOR_MAGENTA);
	else if (player->nbr == 4)
		player->color = ft_strdup(ANSI_COLOR_CYAN);
	else if (player->nbr == 5)
		player->color = ft_strdup(ANSI_COLOR_YELLOW);
	else if (player->nbr == 6)
		player->color = ft_strdup(ANSI_COLOR_BLUE);
	else
		error_init(1);
}
