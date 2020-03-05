/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 17:48:37 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/04 17:48:38 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	valid_flag checks the flag byte and makes sure there are
**	no contradicting flags active.
**
**	if the -dump flag is active, the visualizer gets disabled.
**	if the -v flag is active, the visualizer gets disabled.
*/

static	void	valid_flags(t_env *env)
{
	if ((env->flag_byte & 1) == 0)
		return ;
	if ((env->flag_byte & (1 << 1)) == (1 << 1))
		env->flag_byte 	^= 1;
	else if ((env->flag_byte & (1 << 2)) == (1 << 2))
		env->flag_byte 	^= 1;
	else if ((env->flag_byte & (1 << 3)) == (1 << 3))
		env->flag_byte 	^= 1;
}

/*
**	get_verbosity retrieves the verbosity level for the -v flag
**	if verbosity is 2 or 18 (16 + 2) --> enable cycle verbosity
**	if verbosity is 16 or 18 (16 + 2) --> enable operation verbosity
*/

static	void	get_verbosity(int curr_arg, int arg_nb, char **argv, t_env *env)
{
	long long int verbosity;

	if (curr_arg == arg_nb - 1)
		error_input(10);
	verbosity = ft_atoilong(argv[curr_arg + 1]);
	if (verbosity != 16 && verbosity != 18 && verbosity != 2)
		error_input(11);
	if (verbosity == 18 || verbosity == 2)
		env->flag_byte |= (1 << 3);
	if (verbosity == 2)
		env->flag_byte ^= (1 << 2);
	env->verbosity = (unsigned)verbosity;
}

/*
**	get_dump_cycle retrieves the nbr_cycle argument for the -dump flag.
**	if the dump_cycle is higher than CYCLE_TO_DIE --> -dump flag is disabled.
*/

static	void	get_dump_cycle(int curr_arg, int arg_nb, char **argv, t_env *env)
{
	long long int nbr_cycle;

	if (curr_arg == arg_nb - 1)
		error_input(7);
	nbr_cycle = ft_atoilong(argv[curr_arg + 1]);
	if (nbr_cycle < 1 || 2147483648 < nbr_cycle)
		error_input(8);
	env->dump_cycle = (unsigned)nbr_cycle;
}

/*
**	parse all arguments
**
**	flags:
**
**	-visual --> enables visualizer
**	-dump <nbr_of_cycles> --> dumb memory after <nbr_of_cycles> cycles. --> disables visualizer
**	-v <verbosity level> --> print all performed operations --> disables visualizer
*/

void	parse_args(int arg_nb, char **argv, t_env *env)
{
	int		i;
	char	*player;

	i = 1;
	while (i < arg_nb)
	{
		if (ft_strcmp(argv[i], "-visual") == 0)
			env->flag_byte = env->flag_byte | 1;
		else if (ft_strcmp(argv[i], "-dump") == 0)
		{
			env->flag_byte = env->flag_byte | (1 << 1);
			get_dump_cycle(i, arg_nb, argv, env);
			i++;
		}
		else if (ft_strcmp(argv[i], "-v") == 0)
		{
			env->flag_byte = env->flag_byte | (1 << 2);
			get_verbosity(i, arg_nb, argv, env);
			i++;
		}
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
	if (env->total_players == 0)
		error_input(9);
	valid_flags(env);
}