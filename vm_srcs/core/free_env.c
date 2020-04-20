/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	free a player
**
**	@param player	:	the player to be freed.
**	@param size		:	the size of the player
**
**	note: 	player type is void so that the function can be
**			passed to ft_lstdel.
*/

static	void	free_player(void *player, size_t size)
{
	t_player *local;

	local = (t_player *)player;
	if (size > 0)
	{
		free(local->header);
		free(local);
	}
}

/*
**	@brief:	free a cursor
**
**	@param cursor
**
**	free a cursor and its registries
*/

static	void	free_cursor(t_cursor *cursor)
{
	free(cursor->registries);
	free(cursor);
}

/*
**	@brief:	free the cursor stack
**
**	@param cursor_stack
**
**	iterates through the cursor stack and frees each cursor
**	by calling free cursor.
*/

static	void	free_cursor_stack(t_cursor **cursor_stack)
{
	t_cursor	*iter;
	t_cursor	*trail;

	iter = *cursor_stack;
	while (iter)
	{
		trail = iter;
		iter = iter->next;
		free_cursor(trail);
	}
	*cursor_stack = NULL;
}

/*
**	@brief:	free the global environment struct
**
**	@param env	:	global environment struct
**
**	once the main process has finished, free_env is called
**	to clean up remaining allocated memory in the env struct.
*/

void			free_env(t_env **env)
{
	if ((*env)->players != NULL)
		ft_lstdel(&(*env)->players, &free_player);
	if ((*env)->cursor_stack != NULL)
		free_cursor_stack(&(*env)->cursor_stack);
	if ((*env)->map != NULL)
		free((*env)->map);
	if ((*env)->datamap != NULL)
		free((*env)->datamap);
	free(*env);
	*env = NULL;
}
