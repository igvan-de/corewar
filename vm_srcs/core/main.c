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
**	parse all arguments
*/

static	void	parse_args(int arg_nb, char **argv, t_env *env)
{
	int		i;
	char	*player;

	if (arg_nb > 8)
		error_input(5);
	i = 1;
	while (i < arg_nb)
	{
		if (ft_strcmp(argv[i], "-visual") == 0)
			env->flag_byte = env->flag_byte | 1;
		else if (i == 1 && ft_strcmp(argv[i], "-help") == 0)
			exit_usage();
		else
		{
			player = argv[i];
			add_player(player, env);
		}
		if (env->total_players > MAX_PLAYERS)
			error_input(6);
		i++;
	}
}

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
	load_players(env);
	init_cursors(env);
	exec_corewar(env);
	if ((env->flag_byte & 1) == 1)
		endwin();
	free_env(&env);
	return (0);
}
