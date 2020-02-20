/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   to_2bytes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 12:31:14 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/20 12:31:15 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	to_2bytes takes two bytes and returns them in their
**	two byte representation.
*/

short	to_2bytes(unsigned char one, unsigned char two)
{
	short ret;

	ret = 0;
	ret = ret | ((short)one) << 8;
	ret = ret | (short)two;
	return (ret);
}
