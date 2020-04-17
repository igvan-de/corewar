/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_bits.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 18:03:45 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 17:20:53 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	print a byte in binary
**
**	@param octet	:	byte
**
**	print_bits is a debug function which can be used
**	to print a byte in its binary representation.
*/

void	print_bits(unsigned char octet)
{
	int	i;

	i = 128;
	while (i)
	{
		(octet / i) ? write(1, "1", 1) : write(1, "0", 1);
		(octet / i) ? octet -= i : 0;
		i /= 2;
	}
	ft_putchar('\n');
}
