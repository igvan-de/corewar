/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 15:46:14 by igvan-de       #+#    #+#                */
/*   Updated: 2020/02/18 11:45:24 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 0)
		input_error();
	while (argv[i])
	{
		i++;
	}
	return (0);
}
