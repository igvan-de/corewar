/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/07 17:54:15 by igvan-de       #+#    #+#                */
/*   Updated: 2020/04/03 03:45:50 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	insert_info_into_node(t_func_list *list,
		t_direction *new, int last_index)
{
	int i;

	last_index *= 2;
	i = 0;
	check_sort(list, new, i);
	insert_operation(list, new);
}

void	insert_file_node(t_func_list *list)
{
	int last_index;
	t_direction *new;

	last_index = 0;
	new = NULL;
	add_instruction_node(list, &new, &last_index);
	insert_info_into_node(list, new, last_index);
	list->total_bytes += new->byte_size;
}

void	process_line_into_list(t_func_list *list)
{
	ft_printf("test 2 \n");
	while (ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
	if (list->line[list->line_char] == '.')
	{
		list->line_char++;
		get_name_or_comment(list);
	}
	else if(list->name != NULL)
		insert_file_node(list);
	else
		error_message(list, 20, 0, 2);	
}