/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   modi.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	verify index at memory access
**
**	@param index	:	access index
**
**	modi is used to verify that an index does not exceed memory bounds
**	within the corewar program. If an index exceeds memory bounds it is circled
**	back to start because corewar memory is circular. Modi is used every time
**	an operation tries to access memory.
*/

unsigned int	modi(int index)
{
	if ((index & (MEM_SIZE - 1)) < 0)
		return ((index & (MEM_SIZE - 1)) + MEM_SIZE);
	return (index & (MEM_SIZE - 1));
}
