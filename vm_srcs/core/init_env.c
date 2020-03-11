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
**	@brief:	initialize the memory and player_pos maps 
**
**	@param env	: global environment struct
**
**	init_maps allocates the main memory area where
**	the program's main process will take place. A second area
**	is allocated to keep track of player positions. 
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
**	@brief:	initialize the global environment struct 
**
**	@param env	: global environment struct
**
**	the env struct is used to store data pointers and variables
**	detailing game state. in init_env this structure is allocated
**	and initialized. 
*/

void			init_env(t_env **env)
{
	(*env) = (t_env *)malloc(sizeof(t_env));
	if (!*env)
		error_mem();
	(*env)->flag_byte = 0;
	(*env)->total_players = 0;
	(*env)->players = NULL;
	(*env)->total_cursors = 0;
	(*env)->cursor_stack = NULL;
	init_maps(env);
	load_optab(*env);
	(*env)->player_last_alive = 0;
	(*env)->cycles = 0;
	(*env)->total_cycles = 0;
	(*env)->cycle_last_check = 0;
	(*env)->live_counter = 0;
	(*env)->cycles_to_die = CYCLE_TO_DIE;
	(*env)->checks_counter = 0;
	(*env)->dump_cycle = 0;
	(*env)->verbosity = 0;
}
