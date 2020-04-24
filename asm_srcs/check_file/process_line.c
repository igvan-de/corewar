/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/07 17:54:15 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/22 19:53:48 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** search for the next existing node and saves the pointer to it.
** it will set the new_node back to 0
** so it can make a new node in the next iteration
*/

static void	search_last_node(t_func_list *list, t_direction **ptr)
{
	t_direction *iter;

	iter = list->info;
	while (iter && iter->next)
		iter = iter->next;
	(*ptr) = iter;
	list->new_node = 0;
}

/*
** this will call the check for valid operation.
** then it calls it to process the valid operation.
*/

static void	insert_info_into_node(t_func_list *list,
		t_direction *new)
{
	int i;

	i = 0;
	check_sort(list, new, i);
	insert_operation(list, new);
}

/*
** here it will make a new node of t_direction and it saves the pointer of it
** if there was an label name only present in the last line the pointer will aim
** to the last malloced node
*/

static void	insert_file_node(t_func_list *list)
{
	t_direction *new;

	new = NULL;
	if (list->new_node == 1)
		search_last_node(list, &new);
	else
		add_instruction_node(list, &(list->info), &new);
	insert_info_into_node(list, new);
}

/*
** here it checks if it starts with a .name or .comment
** it doesnt matter which order. if .name has not been given
** and there is an valid operation the program stops.
** if there already is a valid .name and there anything else it goes
** into insert_file_node to further process
*/

void		process_line(t_func_list *list)
{
	while (list->line[list->line_char] &&
	ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
	if (list->line[list->line_char] == '.')
	{
		list->line_char++;
		get_name_comment(list);
	}
	else if (list->name != NULL)
		insert_file_node(list);
	else
		error_message(list, 20, 0, 2);
}
