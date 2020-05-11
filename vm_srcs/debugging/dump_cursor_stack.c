/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_cursor_stack.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	dump_registry(int *registries)
{
	int i;

	ft_putstr("registries: ");
	i = 0;
	while (i < REG_NUMBER)
	{
		ft_putnbr(registries[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

/*
**	@brief:	print the contents of a cursor to stdout
**
**	@param cursor		:	ptr to target cursor
**
**	dump_cursor is a debug function with which the contents of a
**	cursor struct can be printed to stdout.
*/

static	void	dump_cursor(t_cursor *cursor)
{
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
	dump_registry(cursor->registries);
}

/*
**	@brief:	print the contents of the entire cursor stack to stdout
**
**	@param cursor_stack		:	target cursor stack
**
**	dump_cursor_stack is a debug function that prints the entire
**	cursor stack to stdout with repeated calls to dump_cursor.
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
