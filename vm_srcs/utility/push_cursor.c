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
