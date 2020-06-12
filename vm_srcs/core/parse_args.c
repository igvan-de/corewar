/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
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
**	->	if the -v flag is active, the visualizer gets disabled.
**	->	if the -a flag is active, the visualizer gets disabled.
**	->  if the -L flag is active, the visualizer gets disabled.
*/

static	void	valid_flags(t_env *env)
{
	if ((env->flag_byte & (1 << 1)) == (1 << 1) &&
		(env->flag_byte & (1 << 6)) == (1 << 6))
		error_init(3);
	if ((env->flag_byte & 1) == 0)
		return ;
	if ((env->flag_byte & (1 << 1)) == (1 << 1))
		env->flag_byte ^= 1;
	else if ((env->flag_byte & (1 << 2)) == (1 << 2))
		env->flag_byte ^= 1;
	else if ((env->flag_byte & (1 << 3)) == (1 << 3))
		env->flag_byte ^= 1;
	else if ((env->flag_byte & (1 << 4)) == (1 << 4))
		env->flag_byte ^= 1;
	else if ((env->flag_byte & (1 << 5)) == (1 << 5))
		env->flag_byte ^= 1;
	else if ((env->flag_byte & (1 << 6)) == (1 << 6))
		env->flag_byte ^= 1;
}

/*
**	@brief: validate flag parameter
**
**	@param param			:	program parameter
**
**	is_flag receives a parameter passed to corewar
**	and checks if that parameter is a valid flag call.
**	returns 1 if true, 0 if false.
*/

static	int		is_flag(char *param)
{
	if (ft_strncmp(param, "-", 1) == 1)
		return (0);
	else if (ft_strcmp(param, "-visual") == 0)
		return (1);
	else if (ft_strcmp(param, "-dump") == 0)
		return (1);
	else if (ft_strcmp(param, "-d") == 0)
		return (1);
	else if (ft_strcmp(param, "-v") == 0)
		return (1);
	else if (ft_strcmp(param, "-help") == 0)
		return (1);
	else if (ft_strcmp(param, "-n") == 0)
		return (1);
	else if (ft_strcmp(param, "-a") == 0)
		return (1);
	else if (ft_strcmp(param, "-L") == 0)
		return (1);
	return (0);
}

/*
**	@brief:	parse and interpret program parameters
**
**	@param arg_nb	:	number of parameters
**	@param argv		:	parameters
**	@param env		:	global environment struct
**
**	parse_args iterates through the parameters passed to the program
**	and performs action based on the type of the parameter.
**
**	->	if the parameter is a flag, the related bit in the flag byte
**		is turned on. for the '-dump' and '-v' flag, the parameter
**		directly after the flag is saved as either the dump cycle
**		or the verbosity level.
**
**	->	otherwise, the parameter is assumed to be a player file
**		and is processed with add_player.
**
**	->	if the number of players is higher than MAX_PLAYERS or
**		if there are no players, the program exits with error.
**
**	lastly, valid_flags gets called to make sure there are no
**	contradicting flags turned on.
*/

void			parse_args(int arg_nb, char **argv, t_env *env)
{
	int		i;

	i = 1;
	while (i < arg_nb)
	{
		if (is_flag(argv[i]) == 1)
			process_flag(argv, &i, arg_nb, env);
		else
			add_player(argv[i], env);
		i++;
	}
	if (env->total_players > MAX_PLAYERS)
		error_input(6);
	if (env->total_players == 0)
		error_input(9);
	valid_flags(env);
	nbr_players(env);
}
