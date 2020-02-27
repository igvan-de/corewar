/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_total_arg_size.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 08:47:58 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 08:48:00 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	get_total_arg_size receives an encoding byte, and returns
**	the combined size of all arguments noted in the encoding byte.
*/

unsigned char	get_total_arg_size(unsigned char op_code, unsigned char encode)
{
	unsigned char total_arg_size;

	total_arg_size = 0;
	total_arg_size += get_arg_size(op_code, get_bit(encode, 0), get_bit(encode, 1));
	total_arg_size += get_arg_size(op_code, get_bit(encode, 2), get_bit(encode, 3));
	total_arg_size += get_arg_size(op_code, get_bit(encode, 4), get_bit(encode, 5));
	return (total_arg_size);
}
