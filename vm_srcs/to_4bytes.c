/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   to_4bytes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 12:33:02 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/20 12:33:02 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	to_4bytes takes two shorts (2 bytes) and returns them
**	in their 4 byte representation. (int)
*/

int		to_4bytes(unsigned short one, unsigned short two)
{
	int ret;

	ret = 0;
	ret = ret | ((int)one) << 16;
	ret = ret | (int)two;
	return (ret);
}
