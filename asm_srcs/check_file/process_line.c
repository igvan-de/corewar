/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/07 17:54:15 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/09 03:11:03 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	search_last_node(t_func_list *list, t_direction **ptr)
{
	t_direction *iter;

	iter = list->info;
	while (iter && iter->next)
		iter = iter->next;
	(*ptr) = iter;
	list->new_node = 0;
}

void	insert_info_into_node(t_func_list *list,
		t_direction *new)
{
	int i;

	i = 0;
	check_sort(list, new, i);
	insert_operation(list, new);
}

void	insert_file_node(t_func_list *list)
{
	t_direction *new;

	new = NULL;
	if (list->new_node == 1)
		search_last_node(list, &new);
	else
		add_instruction_node(list, &(list->info), &new);
	insert_info_into_node(list, new);
}

void	process_line_into_list(t_func_list *list)
{
	while (list->line[list->line_char] && ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
	if (list->line[list->line_char] == '.')
	{
		list->line_char++;
		get_name_or_comment(list);
	}
	else if (list->name != NULL)
		insert_file_node(list);
	else
		error_message(list, 20, 0, 2);
}