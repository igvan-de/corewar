/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_carry.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 09:02:40 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:12:55 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_carry(t_cursor *cursor, int mode)
{
	if (mode == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}
