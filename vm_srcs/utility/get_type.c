/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_type.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 08:42:10 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/10 08:42:10 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	get_type(unsigned char encode, int arg_num)
{
	unsigned char bitpair;
	unsigned char bit1;
	unsigned char bit2;

	bitpair = 0;
	bit1 = 0;
	bit2 = 0;
	if (arg_num == 1)
	{
		bit1 = get_bit(encode, 0);
		bit2 = get_bit(encode, 1);
	}
	else if (arg_num == 2)
	{
		bit1 = get_bit(encode, 2);
		bit2 = get_bit(encode, 3);
	}
	else if (arg_num == 3)
	{
		bit1 = get_bit(encode, 4);
		bit2 = get_bit(encode, 5);
	}
	else
		error_exec(4);
	bit1 <<= 1;
	bitpair = (unsigned char)bit1 | bit2;
	return (bitpair);
}