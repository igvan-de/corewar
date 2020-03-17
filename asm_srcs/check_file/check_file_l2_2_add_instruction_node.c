/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l2_2_add_instruction_node.c             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 11:09:42 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/17 06:01:27 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_new_node(t_direction **iter)
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
		t_direction *pointer, int *last_index)
{
	t_direction *iter;

	iter = list->info;
	if (iter == NULL)
	{
		/* ft_memalloc zet alle waardes in struct al naar 0/NULL. scheelt weer een lijn
		** want dan is init_new_direction niet meer nodig
		*/
		// iter = (t_direction *)ft_memalloc(sizeof(t_direction));
		iter = (t_direction *)malloc(sizeof(t_direction));
		if (!iter)
			error_messege(list, 7, 2);
	}
	else
	{
		while (iter)
		{
			*last_index = iter->byte_index;
			iter = iter->next;
		}
		/* ft_memalloc zet alle waardes in struct al naar 0/NULL. scheelt weer een lijn*/
		// iter = (t_direction *)ft_memalloc(sizeof(t_direction));
		iter = (t_direction *)malloc(sizeof(t_direction));
		if (!iter)
			error_messege(list, 8, 2);
	}
	init_new_node(&iter);
	pointer = iter;
	return (0);
}
