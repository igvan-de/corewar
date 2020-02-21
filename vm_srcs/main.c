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

static	void	init_map(t_env **env)
{
	(*env)->map = ft_strnew(MEM_SIZE);
	if(!(*env)->map)
		error_mem();
}

static	void	init_env(t_env **env)
{
	(*env) = (t_env *)malloc(sizeof(t_env));
	if (!*env)
		error_mem();
	(*env)->players = 0;
	(*env)->player = NULL;
	(*env)->map = NULL;
	load_optab(*env);
}

/*
**	parse all arguments
*/

static	void	parse_args(int arg_nb, char **argv, t_env *env)
{
	int i;
	char *player;

	i = 1;
	while (i < arg_nb)
	{
		player = argv[i];
		dump_champ_code(player, env);
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

	if (argc != 2)															// only support one argument right now
		exit_usage();

	ft_putstr("\n\n<------------- Welcome to Corewar! ------------>\n\n");

	init_env(&env);
	parse_args(argc, argv, env);
	init_map(&env);
	load_players(env);
	dump_mem(env);
	return (0);
}
