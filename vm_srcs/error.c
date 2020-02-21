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

void	error_mem()
{
	ft_putendl("	memory_error: could not allocate memory.");
	exit (0);
}

void	error_input(int err_code)
{
	if (err_code == 1)
		ft_putendl("	input_error: could not open file.");
	else if (err_code == 2)
		ft_putendl("	input_error: bytes read into header did not match target bytes.");
	else if (err_code == 3)
		ft_putendl("	input_error: found wrong magic value in .cor file.");
	else if (err_code == 4)
		ft_putendl("	input_error: bytes read into execution code buffer did not match target bytes.");
	else if (err_code == 5)
		ft_putendl("	input_error: too many arguments provided");
	exit (0);
}

void	error_init(int err_code)
{
	if (err_code == 1)
		ft_putendl("	init_error: invalid player number encountered.");
	exit (0);
}