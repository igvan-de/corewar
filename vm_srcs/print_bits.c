/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_bits.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 18:03:45 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/19 18:03:46 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	print_bits prints octet in binary to stdout.
*/

void	print_bits(unsigned char octet)
{
	int	i;

	i = 128;
	while (octet >= 0 && i)
	{
		(octet / i) ? write(1, "1", 1) : write(1, "0", 1);
		(octet / i) ? octet -= i : 0;
		i /= 2;
	}
}