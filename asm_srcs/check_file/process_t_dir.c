/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_t_dir.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:13:15 by mark          #+#    #+#                 */
/*   Updated: 2020/05/04 04:49:15 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** T_DIR argument type is a special one cause the T_DIR size can change based
** on the operation.
** This function insert the t_dir on iteration based in encode byte
** then it will add the byte size to the node and the total amount of byte
** the number is stored in args_num in the current node
** the number is stored based on the iteration.
** if it the first number then its stored in the 1st position of the arg_num etc
** its possible to be an label name.
** its a reference to the index from the targeted label
** same with arg_num it will be stored in arg_str.
** it will will be processed afterwards into a number
*/

/*
** @brief	get t_dir size base on operation number
**
** @param	op_code = operation number
*/

static int	get_dir_size(int op_code)
{
	const int dir_size[16] = {4, 4, 4, 4, 4, 4, 4, 4,
	2, 2, 2, 2, 4, 2, 2, 4};

	return (dir_size[op_code - 1]);
}

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
** @brief	process t_dir type argument
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

void		process_t_dir(t_func_list *list, t_direction *new, int arg)
{
	int dir_size;
	int converted;

	dir_size = get_dir_size(new->op_code);
	new->byte_size += dir_size;
	list->total_bytes += dir_size;
	insert_encode(new, arg, DIR_CODE);
	list->line_char++;
	if (list->line[list->line_char] == LABEL_CHAR)
	{
		new->label_in_op = 1;
		get_label_op(list, new, arg);
		return ;
	}
	else if (!((list->line[list->line_char] >= '0' &&
		list->line[list->line_char] <= '9') ||
	list->line[list->line_char] == '-'))
		error_message(list, 110, 0, 11);
	else
	{
		converted = pm_atoi(list);
		new->arg_num[arg] = converted;
	}
	check_between(list, 112, 0, 11);
}
