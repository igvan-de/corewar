/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   to_4bytes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	merge two shorts into an int
**
**	@param one	:	short one
**	@param two	:	short two
*/

int		to_4bytes(unsigned short one, unsigned short two)
{
	int ret;

	ret = 0;
	ret = ret | ((int)one) << 16;
	ret = ret | (int)two;
	return (ret);
}
