/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   to_2bytes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 12:31:14 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:29:16 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

short	to_2bytes(unsigned char one, unsigned char two)
{
	short ret;

	ret = 0;
	ret = ret | ((short)one) << 8;
	ret = ret | (short)two;
	return (ret);
}
