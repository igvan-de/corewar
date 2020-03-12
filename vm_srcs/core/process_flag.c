/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_flag.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/12 12:59:09 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/12 12:59:10 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

void	process_flag(char **argv, int *i, int arg_nb, t_env *env)
{
	if (ft_strcmp(argv[*i], "-visual") == 0)
		env->flag_byte = env->flag_byte | 1;
	else if (ft_strcmp(argv[*i], "-dump") == 0)
	{
		env->flag_byte = env->flag_byte | (1 << 1);
		get_dump_cycle(*i, arg_nb, argv, env);
		(*i)++;
	}
	else if (ft_strcmp(argv[*i], "-v") == 0)
	{
		env->flag_byte = env->flag_byte | (1 << 2);
		get_verbosity(*i, arg_nb, argv, env);
		(*i)++;
	}
	else if (ft_strcmp(argv[*i], "-help") == 0)
		exit_usage();
}
