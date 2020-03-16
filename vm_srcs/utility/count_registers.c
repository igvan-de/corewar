/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_registers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 08:39:50 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:27:27 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
