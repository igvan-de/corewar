/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_env_state.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	print the contents of the env struct to stdout.
**
**	@param env		:	global environment struct
**
**	dump_env_state is a debug function with which the contents of the
**	env struct can be printed to stdout.
*/

void	dump_env_state(t_env *env)
{
	ft_putstr("\n\n<------ ENV STATE DUMP ------->\n\n\n");
	ft_putstr("		flag_byte:		");
	print_bits(env->flag_byte);
	ft_printf("		total players: %u\n", env->total_players);
	ft_printf("		total cursors: %u\n", env->total_cursors);
	ft_printf("		player last alive: %u\n", env->player_last_alive);
	ft_printf("		cycles: %u\n", env->cycles);
	ft_printf("		total_cycles: %u\n", env->total_cycles);
	ft_printf("		cycle nbr of last check: %u\n", env->cycle_last_check);
	ft_printf("		live counter: %u\n", env->live_counter);
	ft_printf("		cycles to die: %u\n", env->cycles_to_die);
	ft_printf("		checks counter: %u\n", env->checks_counter);
	ft_printf("		map: %p\n", env->map);
	ft_printf("		player_pos: %p\n", env->datamap);
	ft_printf("		cursor stack: %p\n", env->cursor_stack);
}
