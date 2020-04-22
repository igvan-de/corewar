/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 08:46:02 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/18 08:46:39 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	main entry for corewar
*/

int				main(int argc, char **argv)
{
	t_env *env;

	if (argc < 2)
		exit_usage();
	init_env(&env);
	parse_args(argc, argv, env);

	dump_players(env->players, env);
	exit (0);

	load_players(env);
	init_cursors(env);
	intro_players(env);
	if ((env->flag_byte & 1) == 1)
		init_ncurses(env);
	exec_corewar(env);
	if ((env->flag_byte & 1) == 1)
		endwin();
	announce_winner(env);
	free_env(&env);
	return (0);
}
