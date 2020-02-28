/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_cursor_stack.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 11:10:32 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/25 11:10:33 by jdunnink      ########   odam.nl         */
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

	printf("\n	printing cursor with id: %u\n", cursor->id);
	printf("		cursor has prev ptr: %p\n", cursor->prev);
	printf("		cursor has next ptr: %p\n", cursor->next);
	printf("		jump: %u\n", cursor->jump);
	printf("		carry: %u\n", cursor->carry);
	printf("		last_live: %u\n", cursor->last_live);
	printf("		live_counter: %u\n", cursor->live_counter);
	printf("		op_code: %hhu\n", cursor->op_code);
	printf("		position index: %u\n", cursor->position);
	printf("		wait_cycles: %u\n", cursor->wait_cycles);
	reg = cursor->registries;
	printf("		registries: %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i\n",
		reg[0], reg[1], reg[2], reg[3], reg[4], reg[5],
		reg[6], reg[7], reg[8], reg[9], reg[10], reg[11],
		reg[12], reg[13], reg[14], reg[15]);
}

/*
**	dump_cursor_stack receives a ptr to the cursor_stack
**	and prints the variables of each cursor to stdout.
*/

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
