/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_bit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 18:00:27 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:23:06 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	get_bit(unsigned char octet, int index)
{
	int shift_right;

	if (index < 0 || index > 8)
		return (-1);
	shift_right = 7;
	octet = octet << index;
	octet = octet >> shift_right;
	if ((1 & octet) == 1)
		return (1);
	return (0);
}
