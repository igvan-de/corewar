/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_registers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	count the operation arguments that are registries
**
**	@param encode	:	encode byte
**
**	count_registers receives an encode byte and counts the bitpairs
**	within this encode byte that represent registries.
*/

int	count_registers(unsigned char encode)
{
	int one;
	int two;
	int regs;

	regs = 0;
	one = get_bit(encode, 0);
	two = get_bit(encode, 1);
	if (one == 0 && two == 1)
		regs++;
	one = get_bit(encode, 2);
	two = get_bit(encode, 3);
	if (one == 0 && two == 1)
		regs++;
	one = get_bit(encode, 4);
	two = get_bit(encode, 5);
	if (one == 0 && two == 1)
		regs++;
	return (regs);
}
