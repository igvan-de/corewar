/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_t_ind.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:13:13 by mark          #+#    #+#                 */
/*   Updated: 2020/05/11 02:17:28 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief	store arguments label in array
**
** @param	list = the container where we store all our information
** @param	list->line_char = keep track the index accesed in line.
** @param	new = memory adress from a new or existing list.
**			it always has the last node in the list
**			this list contains all the information for a operation
** @param	new->arg_str = an array of string to store operation labels
*/

static void	get_label_op(t_func_list *list, t_direction *new, int arg)
{
	int i;

	i = list->line_char + 1;
	while (check_label_char(list->line[i]) == true)
		i++;
	if (ft_isspace(list->line[i]) == 0 && (list->line[i] != SEPARATOR_CHAR &&
	list->line[i] != '\0'))
		error_message(list, 111, 0, 11);
	i--;
	new->arg_str[arg] = ft_strsub(list->line,
		list->line_char + 1, i - list->line_char);
	list->line_char = i + 1;
}

/*
** @brief	process t_ind type argument
**
** @param	list = the container where we store all our information
** @param	list->line_char = keep track the index accesed in line.
** @param	list->total_bytes = keeps track of the amount of bytes
** @param	new = memory adress from a new or existing list.
**			it always has the last node in the list
**			this list contains all the information for a operation
** @param	new->label_in_op = check if there is a label name argument
** @param	new->byte_size = size of the operation
** @param	new->arg_num = an array of ints to store operation arguments
** @param	arg = which argument of the operation it is
**
** adjust the byte size of the operation node and the total bytes
** it also insert the encode byte
** it checks if there is a label or a number and store them in there array
*/

void		process_t_ind(t_func_list *list, t_direction *new, int arg)
{
	int converted;

	list->total_bytes += 2;
	new->byte_size += 2;
	converted = 0;
	insert_encode(new, arg, IND_CODE);
	if (list->line[list->line_char] == LABEL_CHAR)
	{
		new->label_in_op = 1;
		get_label_op(list, new, arg);
		return ;
	}
	else if (!((list->line[list->line_char] >= '0' &&
		list->line[list->line_char] <= '9') ||
	list->line[list->line_char] == '-'))
		error_message(list, 101, 0, 10);
	else
	{
		converted = pm_atoi(list);
		new->arg_num[arg] = converted;
	}
	check_between(list, 100, 0, 10);
	new->arg_num[arg] = converted;
}
