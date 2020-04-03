/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_instruction_node.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 11:09:42 by mlokhors       #+#    #+#                */
/*   Updated: 2020/04/03 02:44:08 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** adds a node to the list and set them to 0
*/

void	init_args(t_func_list *list, t_direction *iter)
{
	iter->arg_str = ft_memalloc(sizeof(char *) * 3);
	if (iter->arg_str == NULL)
		error_message(list, 52, 0, 5);
	iter->arg_num = ft_memalloc(sizeof(int) * 3);
	if (iter->arg_num == NULL)
		error_message(list, 53, 0, 5);
}

void	add_instruction_node(t_func_list *list,
		t_direction **pointer, int *last_index)
{
	t_direction *iter;

	iter = list->info;
	if (iter == NULL)
	{
		iter = (t_direction *)ft_memalloc(sizeof(t_direction));
		if (iter == NULL)
			error_message(list, 50, 0, 5);
	}
	else
	{
		while (iter)
		{
			*last_index = iter->byte_index;
			iter = iter->next;
		}
		iter = (t_direction *)ft_memalloc(sizeof(t_direction));
		if (iter == NULL)
			error_message(list, 51, 0, 5);
	}
	init_args(list, iter);
	(*pointer) = iter;
}
