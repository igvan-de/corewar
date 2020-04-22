/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   to_2bytes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	merge two bytes
**
**	@param one	:	byte one
**	@param two	:	byte two
*/

short	to_2bytes(unsigned char one, unsigned char two)
{
	short ret;

	ret = 0;
	ret = ret | ((short)one) << 8;
	ret = ret | (short)two;
	return (ret);
}
