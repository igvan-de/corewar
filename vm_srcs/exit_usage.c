/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_usage.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 14:12:24 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/20 14:12:25 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	exit_usage prints program usage to stdout and exits the program.
*/

void	exit_usage(void)
{
	ft_putendl("corewar: vm development usage:");
	ft_putendl("	./corewar <testfile>.cor");
	exit(0);
}
