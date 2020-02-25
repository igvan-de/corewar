/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 08:34:18 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/25 08:34:18 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	free_player takes a ptr to a player and frees
**	that player's variables and the t_player struct.
*/

static	void	free_player(void *player, size_t size)
{
	t_player *local;

	local = (t_player *)player;
	if (size > 0)
	{
		free(local->header);
		free(local->color);
		free(local->exec_code);
		free(local);
	}
}

/*
**	free_env frees the main environment struct and
**	all its variables if still allocated.
*/

void	free_env(t_env **env)
{
	if ((*env)->players != NULL)
		ft_lstdel(&(*env)->players, &free_player);
	if ((*env)->map != NULL)
		free((*env)->map);
	if ((*env)->player_pos != NULL)
		free((*env)->player_pos);
	free(*env);
	*env = NULL;
}