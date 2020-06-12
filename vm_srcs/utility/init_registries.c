/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_registries.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	initiate process registries
*/

int		*init_registries(void)
{
	int	i;
	int	*new_regs;

	new_regs = (int *)malloc(sizeof(int) * (REG_NUMBER + 1));
	if (!new_regs)
		error_mem();
	i = 0;
	while (i <= REG_NUMBER)
	{
		new_regs[i] = 0;
		i++;
	}
	return (new_regs);
}
