/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   modi.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 09:12:22 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/28 09:12:22 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	modi receives a cursor index and if that cursor index
**	exceeds the memory map, returns the correct index
**	in circular memory. produces error if the provided
**	index is higher than MEM_SIZE * 2.
*/

unsigned int	modi(int index)
{
	if (index >= MEM_SIZE * 2)
		error_exec(1);
	else if (index >= MEM_SIZE)
		return (index - MEM_SIZE);
	else if (index < 0)
		return (index + MEM_SIZE);
	return (index);
}
