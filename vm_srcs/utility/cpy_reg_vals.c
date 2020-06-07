/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cpy_reg_vals.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	copy registry values
**
**	@param dst	:	destination cursor
**	@param src	:	source cursor
**
**	cpy_reg_vals receives two cursors and copies the registry values
**	from the source cursor to the destination cursor.
*/

void	cpy_reg_vals(t_cursor *dst, t_cursor *src)
{
	int i;

	i = 0;
	while (i <= REG_NUMBER)
	{
		dst->registries[i] = src->registries[i];
		i++;
	}
}
