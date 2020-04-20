/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_type.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	load_bits(BYTE *bit1, BYTE *bit2, int i, BYTE encode)
{
	*bit1 = get_bit(encode, i);
	*bit2 = get_bit(encode, i + 1);
}

int				get_type(unsigned char encode, int arg_num)
{
	unsigned char bitpair;
	unsigned char bit1;
	unsigned char bit2;

	bitpair = 0;
	bit1 = 0;
	bit2 = 0;
	if (arg_num == 1)
		load_bits(&bit1, &bit2, 0, encode);
	else if (arg_num == 2)
		load_bits(&bit1, &bit2, 2, encode);
	else if (arg_num == 3)
		load_bits(&bit1, &bit2, 4, encode);
	else
		error_exec(4);
	bit1 <<= 1;
	bitpair = (unsigned char)bit1 | bit2;
	return (bitpair);
}
