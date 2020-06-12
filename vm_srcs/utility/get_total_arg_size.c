/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_total_arg_size.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief: determine the size of all operation arguments combined
**
**	@param op_code	:	operation code
**	@param encode	:	encode byte
**
**	get_total_arg_size receives an encode byte and returns the size of
**	all arguments combined in bytes.
*/

unsigned char	get_total_arg_size(t_byt op_code, t_byt encode)
{
	unsigned char total_arg_size;

	total_arg_size = 0;
	total_arg_size += get_arg_size(op_code,
		get_bit(encode, 0), get_bit(encode, 1));
	total_arg_size += get_arg_size(op_code,
		get_bit(encode, 2), get_bit(encode, 3));
	total_arg_size += get_arg_size(op_code,
		get_bit(encode, 4), get_bit(encode, 5));
	if (op_code == 16 && total_arg_size > 4)
		return (4);
	return (total_arg_size);
}
