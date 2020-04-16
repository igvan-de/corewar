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

/*
**	@brief: set the carry flag
**
**	@param cursor			:	global environment struct
**	@param mode				:	mode type
**
**	set_carry sets the carry flag in the cursor passed as parameter.
**	if set_carry is called with mode 0, the carry is set to 1. Otherwise,
**	the carry is set to 0.
*/

void	set_carry(t_cursor *cursor, int mode)
{
	if (mode == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}
