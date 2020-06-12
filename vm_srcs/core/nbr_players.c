/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**  check if a player nbr is already assigned
*/

static	int		is_assigned(int player_nbr, t_env *env)
{
	t_list		*iter;
	t_player	*player;

	iter = env->players;
	while (iter)
	{
		player = iter->content;
		if (player_nbr == player->nbr)
			return (1);
		iter = iter->next;
	}
	return (0);
}

/*
**  find unassigned player nbr
*/

static	void	verif_player_nbr(t_env *env)
{
	if (is_assigned(env->player_nbr, env) == 1)
	{
		env->player_nbr++;
		verif_player_nbr(env);
	}
}

/*
**  assign player nbr
*/

static	void	assign_nbr(t_env *env, t_player *player)
{
	verif_player_nbr(env);
	player->nbr = env->player_nbr;
	env->player_nbr++;
}

/*
**  assign player nbr for each player
*/

void			nbr_players(t_env *env)
{
	t_list		*iter;
	t_player	*player;

	iter = env->players;
	while (iter)
	{
		player = iter->content;
		if (player->nbr == 0)
			assign_nbr(env, player);
		iter = iter->next;
	}
}
