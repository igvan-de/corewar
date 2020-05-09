/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/07 17:54:15 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/05/09 02:39:48 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief	search for the last node that is half filled in
**
** @param	list = the container where we store all our information
** @param	ptr = memory adress from a  existing list.
**			it always has the last node in the list
**
** search for the half filled node and saves the pointer to it.
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
** @brief	check for name or comment then process rest
**
** @param	list = the container where we store all our information
** @param	new = memory adress from a new or existing list.
**			it always has the last node in the list
**			this list contains all the information for a operation
**
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
** @brief	check for name or comment then process rest
**
** @param	list = the container where we store all our information
** @param	list->new_node = is to keep track if the new node is totally filled
**			or not.
**
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
** @brief	check for name or comment then process rest
**
** @param	list = the container where we store all our information
** @param	list->name = is the name of the champion
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
**
** here it checks if it starts with a .name or .comment
** it doesnt matter which order. if .name has not been given
** and there is an valid operation the program stops.
** if there already is a valid .name and there anything else it goes
** into insert_file_node to further process
*/

void		process_line(t_func_list *list)
{
	skip_space(list);
	if (list->line[list->line_char] &&
		list->line[list->line_char] == '.')
	{
		list->line_char++;
		get_name_comment(list);
	}
	else if (list->name != NULL && list->comment != NULL)
		insert_file_node(list);
	else
		error_message(list, 20, 0, 2);
}
