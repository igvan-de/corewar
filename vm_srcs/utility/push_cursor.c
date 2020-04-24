/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_cursor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	push a cursor unto the cursor stack
**
**	@param c		:	cursor
**	@param stack	:	ptr to cursor stack
*/

void	push_cursor(t_cursor *c, t_cursor **stack)
{
	if (*stack == NULL)
		*stack = c;
	else
	{
		c->next = *stack;
		(*stack)->prev = c;
		*stack = c;
	}
}
