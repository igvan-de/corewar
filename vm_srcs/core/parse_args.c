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

static	int	is_flag(char *param)
{
	if (ft_strncmp(param, "-", 1) == 1)
		return (0);
	else if (ft_strcmp(param, "-visual") == 0)
		return (1);
	else if (ft_strcmp(param, "-dump") == 0)
		return (1);
	else if (ft_strcmp(param, "-v") == 0)
		return (1);
	else if (ft_strcmp(param, "-help") == 0)
		return (1);
	return (0);
}

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
}
