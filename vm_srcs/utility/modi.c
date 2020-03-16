/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   modi.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 09:12:22 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:29:00 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int	modi(int index)
{
	if ((index & (MEM_SIZE - 1)) < 0)
		return ((index & (MEM_SIZE - 1)) + MEM_SIZE);
	return (index & (MEM_SIZE - 1));
}
