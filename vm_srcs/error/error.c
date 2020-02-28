/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 12:29:55 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/21 12:29:55 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	error_mem is the default error handler for memory allocation
**	errors.
*/

void	error_mem(void)
{
	ft_putendl("	memory_error: could not allocate memory.");
	exit(0);
}

/*
**	error_input is the default error handler for errors related
**	to input parsing.
*/

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
		ft_putendl("	input_error 6: too many champions.\n");
	exit(0);
}

/*
**	error_init is the default error handler for errors related
**	to setting up the initial game state.
*/

void	error_init(int err_code)
{
	if (err_code == 1)
		ft_putendl("	init_error 1: invalid player number encountered.");
	else if (err_code == 2)
		ft_putendl("	init_error 2: could not find cursor position.");
	exit(0);
}

/*
**	error_exec is the default error handler for the corewar program
**	execution cycle.
*/

void	error_exec(int err_code)
{
	if (err_code == 1)
		ft_putendl("	exec_error 1: cursor index exceeds circular memory space\n");
	exit(0);
}
