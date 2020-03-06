/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l2_2_add_instruction_node.c             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 11:09:42 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/06 14:04:15 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_new_direction(t_direction **iter)
{
	(*iter)->op_code = 0;
	(*iter)->encode = 0;
	(*iter)->arg_1 = NULL;
	(*iter)->arg_1_number = 0;
	(*iter)->arg_2 = NULL;
	(*iter)->arg_2_number = 0;
	(*iter)->arg_3 = NULL;
	(*iter)->arg_3_number = 0;
	(*iter)->label = NULL;
	(*iter)->byte_index = 0;
	(*iter)->byte_size = 0;
	(*iter)->next = NULL;
}

/*
** adds a node to the list and set them to 0
*/

void	add_instruction_node(t_func_list *list,
		t_direction *pointer, t_count *counter)
{
	t_direction *iter;

	iter = list->info;
	if (iter == NULL)
	{
		iter = (t_direction *)malloc(sizeof(t_direction));
		if (!iter)
			error_messege(list, 7, 2);
	}
	else
	{
		while (iter)
		{
			counter->byte_count = iter->byte_index;
			iter = iter->next;
		}
		iter = (t_direction *)malloc(sizeof(t_direction));
		if (!iter)
			error_messege(list, 8, 2);
	}
	init_new_direction(&iter);
	pointer = iter;
	return (0);
}