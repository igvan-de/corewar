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
	ft_putendl("\n	./corewar <testfile>.cor");
	ft_putendl("		supported champions: 4");
	ft_putendl("		supported ops: live, zjmp, sti, ld");
	ft_putendl("\n	use '-dump' <nbr_cycle> to view memory");
	ft_putendl("	use '-v' <level> to specify verbosity level");
	ft_putendl("		supported verbosity levels: 16");
	ft_putendl("	use '-visual' flag to visualize\n");
	exit(0);
}
