/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_registries.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 14:38:37 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:28:52 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		*init_registries(void)
{
	int	i;
	int	*new_regs;

	new_regs = (int *)malloc(sizeof(int) * (REG_NUMBER));
	if (!new_regs)
		error_mem();
	i = 0;
	while (i < REG_NUMBER)
	{
		new_regs[i] = 0;
		i++;
	}
	return (new_regs);
}
