/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_arg_size.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 08:28:28 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 08:28:29 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	get_arg receives 2 bits and interprets them as a bitpair
**	of an encoding byte. It then returns the size related
**	to the argument type specified by the bitpair.
*/

unsigned char	get_arg_size(int op_code, int one, int two)
{
	if (one == 0 && two == 1)
		return (1);
	else if (one == 1 && two == 0)
		return (get_tdir_size(op_code));
	else if (one == 1 && two == 1)
		return (2);
	return (0);
}
