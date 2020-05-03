/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_usage.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exit_usage(void)
{
	ft_putendl("corewar usage:");
	ft_putendl("\n	./corewar <testfile>.cor");
	ft_putendl("\n	use '-dump' <nbr_cycle> to view memory");
	ft_putendl("	use '-v' <level> to specify verbosity level");
	ft_putendl("		supported verbosity levels:");
	ft_putendl("			16 --> show performed operations");
	ft_putendl("			2 --> show cycles");
	ft_putendl("			verbosity can be combined to enable multiple");
	ft_putendl("	use '-visual' flag to visualize");
	ft_putendl("	use -a flag to enable operation aff\n");
	exit(0);
}
