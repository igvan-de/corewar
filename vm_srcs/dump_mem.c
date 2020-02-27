/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_mem.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 13:35:42 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/21 13:35:43 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	get_player receives a player number and returns
**	a ptr to the player with that number in the env->players
**	list. If the player is not found, the function produces
**	error.
*/

static	t_player	*get_player(int player_nbr, t_env *env)
{
	t_list		*iter;
	t_player	*curr;

	iter = env->players;
	while (iter)
	{
		curr = iter->content;
		if (curr->nbr == player_nbr)
			return (curr);
		iter = iter->next;
	}
	error_init(1);
	return (NULL);
}

/*
**	get_color returns the character string stored
**	in the player struct, so that dump_mem can show the
**	memory map with player colors.
*/

static	char		*get_color(t_env *env, int player_nbr)
{
	t_player *curr;

	curr = get_player(player_nbr, env);
	return (curr->color);
}

/*
**	dump_mem prints the current state of the memory map
**	to stdout.
*/

void				dump_mem(t_env *env)
{
	int i;

	ft_putstr("\n\n<------ MEMORY DUMP ------->\n\n\n");
	i = 1;
	while (i < MEM_SIZE)
	{
		if (env->player_pos[i - 1] != 0)
		{
			printf("%s%02x " ANSI_COLOR_RESET,
				get_color(env, env->player_pos[i - 1]),
				0xFF & env->map[i - 1]);
			fflush(stdout);
		}
		else
		{
			printf("%#02x ", env->map[i - 1]);
			fflush(stdout);
		}
		if (i % 63 == 0)
			ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}
