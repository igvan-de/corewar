/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_cursor_stack.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 11:10:32 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 17:19:11 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	dump_cursor prints the values stored in the cursor
**	passed as argument to stdout.
*/

static	void	dump_cursor(t_cursor *cursor)
{
	int *reg;

	ft_printf("\n	printing cursor with id: %u\n", cursor->id);
	ft_printf("		cursor has prev ptr: %p\n", cursor->prev);
	ft_printf("		cursor has next ptr: %p\n", cursor->next);
	ft_printf("		jump: %u\n", cursor->jump);
	ft_printf("		carry: %u\n", cursor->carry);
	ft_printf("		last_live: %u\n", cursor->last_live);
	ft_printf("		live_counter: %u\n", cursor->live_counter);
	ft_printf("		op_code: %hhu\n", cursor->op_code);
	ft_printf("		position index: %u\n", cursor->position);
	ft_printf("		wait_cycles: %u\n", cursor->wait_cycles);
	reg = cursor->registries;
	ft_printf("		registries: %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i\n",
		reg[0], reg[1], reg[2], reg[3], reg[4], reg[5],
		reg[6], reg[7], reg[8], reg[9], reg[10], reg[11],
		reg[12], reg[13], reg[14], reg[15]);
}

void			dump_cursor_stack(t_cursor *cursor_stack)
{
	t_cursor *iter;

	ft_putstr("\n\n<------ CURSOR STACK DUMP ------->\n\n\n");
	iter = cursor_stack;
	while (iter)
	{
		dump_cursor(iter);
		iter = iter->next;
	}
}
