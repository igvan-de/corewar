/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:01:53 by mark           #+#    #+#                */
/*   Updated: 2020/04/03 02:55:24 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		if_encode(int op_code)
{
	const int	encode[16] = {1, 2, 2, 2, 2, 2, 2, 2, 1,
	2, 2, 1, 2, 2, 1, 2};

	return (encode[op_code - 1]);
}

static void		check_operation(t_func_list *list,
		t_direction *new, int i)
{
	int number;
	int len;
	int op_encode;

	op_encode = 0;
	number = 0;
	len = i - list->line_char;
	if (len > 5 || len <= 0)
		error_message(list, 69, 2, 6);
	number = calc_cmp_operation(list, len);
	if (number == -1)
		error_message(list, 68, 2, 6);
	new->op_code = number;
	op_encode = if_encode(number);
	list->total_bytes += op_encode;
	new->byte_size += op_encode;
	list->line_char = i;
}

static void		get_label_name(t_func_list *list, t_direction *new, int len)
{
	int start;
	int ret;
	char *sub;

	sub = NULL;
	start = list->line_char;
	ret = 0;
	while (list->line_char < len)
	{
		ret = check_label_char(list->line[list->line_char]);
		if (ret == -1)
			error_message(list, 60, 0, 6);
		list->line_char++;
	}
	sub = ft_strsub(list->line, start, len);
	if (sub == NULL)
		error_message(list, 61, 1, 6);
	add_to_hash(list, sub, new->byte_index);
	list->line_char = len;
}

void			check_sort(t_func_list *list,
		t_direction *new, int i)
{
	while (ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
	i = list->line_char;
	while (list->line[i] && ft_isspace(list->line[i]) == 0)
		i++;
	if (list->line[i - 1] == LABEL_CHAR)
	{
		get_label_name(list, new, i);
		list->line_char = i;
		return (check_sort(list, new, i));
	}
	else
		check_operation(list, new, i);
}