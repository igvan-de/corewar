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

static	void	load_bits(t_byt *bit1, t_byt *bit2, int i, t_byt encode)
{
	*bit1 = get_bit(encode, i);
	*bit2 = get_bit(encode, i + 1);
}

/*
**	@brief:	read an argument type from the encode byte
**
**	@param	encode	:	encode byte
**	@param	arg_num	:	argument index
**
**	get_type receives an encode byte and returns the type of the argument
**	at the index arg_num.
*/

int				get_type(t_byt encode, int arg_num)
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
