/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 08:11:19 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/25 08:11:20 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	init_maps allocates memory for the main memory map at
**	env->map and the player position lookup map at env->player_pos.
*/

static	void	init_maps(t_env **env)
{
	(*env)->map = ft_strnew(MEM_SIZE);
	if (!(*env)->map)
		error_mem();
	(*env)->player_pos = ft_strnew(MEM_SIZE);
	if (!(*env)->player_pos)
		error_mem();
}

/*
**	init_env allocates memory for the main environment
**	struct and the memory areas env->map and env->player_pos.
*/

void			init_env(t_env **env)
{
	(*env) = (t_env *)malloc(sizeof(t_env));
	if (!*env)
		error_mem();
	(*env)->total_players = 0;
	(*env)->players = NULL;
	(*env)->total_cursors = 0;
	(*env)->cursor_stack = NULL;
	init_maps(env);
	load_optab(*env);
	(*env)->cycles = 0;
	(*env)->live_counter = 0;
	(*env)->cycles_to_die = CYCLE_TO_DIE;

}
