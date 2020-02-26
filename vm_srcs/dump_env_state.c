/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_env_state.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 08:06:29 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 08:06:30 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	dump_env_state(t_env *env)
{
	ft_putstr("\n\n<------ ENV STATE DUMP ------->\n\n\n");
	printf("		total players: %u\n", env->total_players);
	printf("		total cursors: %u\n", env->total_cursors);
	printf("		player last alive: %u\n", env->player_last_alive);
	printf("		cycles: %u\n", env->cycles);
	printf("		live counter: %u\n", env->live_counter);
	printf("		cycles to die: %u\n", env->cycles_to_die);
	printf("		checks counter: %u\n", env->checks_counter);
	printf("		map: %p\n", env->map);
	printf("		player_pos: %p\n", env->player_pos);
	printf("		cursor stack: %p\n", env->cursor_stack);
}
