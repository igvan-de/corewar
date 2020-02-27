/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_carry.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 09:02:40 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 09:02:40 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	set_carry sets the carry flag of the cursor
**	passed as argument, depending on the mode provided.
**	if mode == 0, carry is set to 1.
**	if mode != 0, carry is set to 0.
*/

void	set_carry(t_cursor *cursor, int mode)
{
	if (mode == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	printf("	ld --> carry for cursor %i is set to %i\n", cursor->id, cursor->carry);
}
