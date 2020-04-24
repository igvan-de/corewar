/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   announce_winner.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	find and return a players' name
**
**	@param env		:	global environment struct
**	@param id		:	unique player id
**	@return char*	:	player name
**
**	player_name iterates through the players list and if it finds the player
**	with the matching id, returns the name of that player.
**	If it could not find the player,
**	the function returns NULL as a string literal.
*/

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

/*
**	@brief:	print the winning player to stdout
**
**	@param env		:	global environment struct
**
**	announce_winner gets called after the corewar main
**	process is finished. It retrieves the id of the last
**	player alive and prints a message, declaring the winner.
*/

void			announce_winner(t_env *env)
{
	ft_putstr("Contestant ");
	ft_putnbr(env->player_last_alive);
	ft_putstr(", \"");
	ft_putstr(player_name(env, env->player_last_alive));
	ft_putstr("\", has won !\n");
}
