/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   to_4bytes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 12:33:02 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:23:12 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		to_4bytes(unsigned short one, unsigned short two)
{
	int ret;

	ret = 0;
	ret = ret | ((int)one) << 16;
	ret = ret | (int)two;
	return (ret);
}
