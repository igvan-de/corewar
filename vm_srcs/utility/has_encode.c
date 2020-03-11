/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   has_encode.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 08:37:46 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:28:45 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	has_encode(unsigned char op_code)
{
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
		return (0);
	return (1);
}
