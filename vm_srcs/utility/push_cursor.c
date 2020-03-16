/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_cursor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 14:36:17 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:22:29 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
