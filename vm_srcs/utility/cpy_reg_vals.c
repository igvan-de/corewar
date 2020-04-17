/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cpy_reg_vals.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 14:44:39 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/10 14:44:40 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cpy_reg_vals(t_cursor *dst, t_cursor *src)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
		dst->registries[i] = src->registries[i];
		i++;
	}
}
