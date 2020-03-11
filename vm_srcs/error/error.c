/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 12:29:55 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 17:22:10 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	error_mem(void)
{
	ft_putendl("	memory_error: could not allocate memory.");
	exit(0);
}

void	error_input(int err_code)
{
	if (err_code == 1)
		ft_putendl("	input_error 1: could not open file.");
	else if (err_code == 2)
		ft_putendl("	input_error 2: inaccurate bytes read into header.");
	else if (err_code == 3)
		ft_putendl("	input_error 3: found wrong magic value in .cor file.");
	else if (err_code == 4)
		ft_putendl("	input_error 4: inaccurate bytes read into exec_code.");
	else if (err_code == 5)
		ft_putendl("	input_error 5: too many arguments provided");
	else if (err_code == 6)
		ft_putendl("	input_error 6: too many champions.");
	else if (err_code == 7)
		ft_putendl("	input_error 7: -dump flag requires <nbr_of_cycles>");
	else if (err_code == 8)
		ft_putendl("	input_error 8: -dump <nbr_cycle> is not a valid cycle.");
	else if (err_code == 9)
		ft_putendl("	input_error 9: no champions provided");
	else if (err_code == 10)
		ft_putendl("	input_error 10: -v flag requires verbosity level.");
	else if (err_code == 11)
		ft_putendl("	input_error 11: specified verbosity level not supported.");
	exit(0);
}

void	error_init(int err_code)
{
	if (err_code == 1)
		ft_putendl("	init_error 1: invalid player number encountered.");
	else if (err_code == 2)
		ft_putendl("	init_error 2: could not find cursor position.");
	exit(0);
}

void	error_exec(int err_code)
{
	if (err_code == 2)
		ft_putendl("	exec_error 2: invalid index encountered while destructing int-value\n");
	else if (err_code == 3)
		ft_putendl("	exec_error 3: incorrect argument size found\n");
	else if (err_code == 4)
		ft_putendl("	exec_error 4: error occurred in get_arg\n");
	exit(0);
}
