/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 17:48:37 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:08:21 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	validate flag byte
**
**	@param env	: global environment struct
**
**	valid_flag checks the flag byte and makes sure there are
**	no contradicting flags active.
**
**	->	if the -dump flag is active, the visualizer gets disabled.
**
**	->	if the -v flag is active, the visualizer gets disabled.
*/

static	void	valid_flags(t_env *env)
{
	if ((env->flag_byte & 1) == 0)
		return ;
	if ((env->flag_byte & (1 << 1)) == (1 << 1))
		env->flag_byte ^= 1;
	else if ((env->flag_byte & (1 << 2)) == (1 << 2))
		env->flag_byte ^= 1;
	else if ((env->flag_byte & (1 << 3)) == (1 << 3))
		env->flag_byte ^= 1;
}

/*
**	@brief: retrieve the verbosity level
**
**	@param curr_arg		: 	number of current parameter
**	@param arg_nb		:	total number of parameters
**	@param argv			:	parameters
**	@param env			:	global environment struct
**
**	after the '-v' flag is encountered, parse_args calls
**	get_verbosity to retrieve the verbosity level from
**	the parameter directly after the flag.
**
**	->	if verbosity is 2 or 18 (16 + 2) --> enable cycle verbosity
**
**	->	if verbosity is 16 or 18 (16 + 2) --> enable operation verbosity
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

/**
**	@brief: retrieve the dump cycle value
**
**	@param curr_arg	:	the number of the current parameter
**	@param arg_nb	:	the total number of parameters
**	@param argv		:	parameters
**	@param env		:	global environment struct
**
**	after the '-dump' flag is encountered, parse_args calls
**	get_dump_cycle to retrieve the dump cycle value from
**	the parameter directly after the flag.
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

void			parse_args(int arg_nb, char **argv, t_env *env)
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
