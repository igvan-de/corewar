/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_t_dir.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:13:15 by mark          #+#    #+#                 */
/*   Updated: 2020/04/15 03:04:28 by mark          ########   odam.nl         */
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
**/

static int	get_dir_size(int op_code)
{
	const int dir_size[16] = {4, 4, 4, 4, 4, 4, 4, 4,
	2, 2, 2, 2, 4, 2, 2, 4};

	return (dir_size[op_code - 1]);
}

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
}
