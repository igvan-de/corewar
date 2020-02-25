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

	if (arg_nb > 7)
		error_input(5);
	i = 1;
	while (i < arg_nb)
	{
		player = argv[i];
		add_player(player, env);
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
	ft_putstr("\n\n<------------- Welcome to Corewar! ------------>\n\n");
	init_env(&env);
	parse_args(argc, argv, env);
	dump_players(env->players, env);
	load_players(env);
	dump_mem(env);
	free_env(&env);
	return (0);
}
