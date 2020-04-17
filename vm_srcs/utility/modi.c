/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   modi.c		                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int	modi(int index)
{
	if ((index & (MEM_SIZE - 1)) < 0)
		return ((index & (MEM_SIZE - 1)) + MEM_SIZE);
	return (index & (MEM_SIZE - 1));
}
