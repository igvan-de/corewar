/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_t_dir.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:13:15 by mark           #+#    #+#                */
/*   Updated: 2020/04/03 04:41:41 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_dir_size(int op_code)
{
	const int dir_size[16] = {4, 4, 4, 4, 4, 4, 4, 4,
	2, 2, 2, 2, 4, 2, 2, 4};

	return (dir_size[op_code - 1]);
}

void		get_label_op(t_func_list *list, t_direction *new, int arg)
{
	int i;

	i = list->line_char;
	while (check_label_char(list->line[i]) == true)
		i++;
	if (ft_isspace(list->line[i]) == 0 && list->line[i] != SEPARATOR_CHAR)
		error_message(list, 110, 0, 11);
	i--;
	new->arg_str[arg] = ft_strsub(list->line, list->line_char, i - list->line_char);
	list->line_char = i + 1;
}

void		process_t_dir(t_func_list *list, t_direction *new, int arg)
{
	int dir_size;
	int converted;

	dir_size =  get_dir_size(new->op_code);
	new->byte_size += dir_size;
	list->total_bytes += dir_size;
	insert_encode(new, arg, DIR_CODE);
	list->line_char++;
	if (list->line[list->line_char] == LABEL_CHAR)
	{
		new->label_in_op = 1;
		get_label_op(list, new, arg);
	}
	else if (!(list->line[list->line_char] >= '0' && list->line[list->line_char] <= '9'))
		error_message(list, 110 ,0, 11);
	else
	{
		converted = pm_atoi(list);
		new->arg_num[arg] = converted;
	}
}