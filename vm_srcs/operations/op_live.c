/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_live.c                                          :+:    :+:            */
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
**	@brief:	send a live signal
**
**	@param cursor		:	target cursor
**	@param env 			:	global environment struct
**
**	op_live is an operation function that is used by corewar champions
**	to send live signals. The player_last_alive variable of the env
**	struct is only updated if the value in the first registry matches
**	the value provided to op_live as argument.
*/

void			op_live(t_cursor *cursor, t_env *env)
{
	int		value;

	value = get_tdir(env, modi(cursor->position + 1));
	if (value == cursor->registries[1])
	{
		env->player_last_alive = value * -1;
		if ((env->flag_byte & (1 << 5)) == (1 << 5))
		{
			ft_printf("A process shows that player %i (%s) is still alive.\n",
				value * -1, player_name(env, value * -1));
		}
	}
	env->live_counter++;
	cursor->last_live = env->total_cycles;
	cursor->live_counter++;
	move_cursor(cursor, env);
}
