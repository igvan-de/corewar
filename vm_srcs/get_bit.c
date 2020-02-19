/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_bit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 18:00:27 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/19 18:00:27 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	get_bit returns the bit (0 or 1) at the index within octet.
**	If the index is not within byte-range, the function returns -1.
*/

int get_bit(unsigned char octet, int index)
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