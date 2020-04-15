/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:01:53 by mark          #+#    #+#                 */
/*   Updated: 2020/04/15 05:50:15 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		if_encode(int op_code)
{
	const int	encode[16] = {1, 2, 2, 2, 2, 2, 2, 2, 1,
	2, 2, 1, 2, 2, 1, 2};

	return (encode[op_code - 1]);
}

/*
** check if its an valid op_code.
** Also it checks if there is an encode byte
** it will add to the total bytes but to the node byte amount
*/

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

/*
** checks the label with correct chars then it makes a sub string.
** after the substring has been made it will convert to a hash
** it will be added into a new list that remembers the hash.
** and the index. so once everything is finished it can easily
** convert labels to the indirect value based on the index
*/

static void		get_label_name(t_func_list *list,
				int len)
{
	int		start;
	int		ret;
	char	*sub;

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
	sub = ft_strsub(list->line, start, len - 1);
	if (sub == NULL)
		error_message(list, 61, 1, 6);
	add_to_hash(list, sub);
	list->line_char = len;
}

/*
** this is quite a heavy read. so it first check for a label name
** if this has been found it will process then it will recurse so it
** will check again. because its already been found it will skip this
** and goes straight to the process the remaining arguments.
** or it stops since the the end of line have been found.
** it wil set list->new_node to 1 so no new node is being made
*/

void			check_sort(t_func_list *list,
		t_direction *new, int i)
{
	while (list->line[list->line_char] &&
		ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
	i = list->line_char;
	while (list->line[i] && ft_isspace(list->line[i]) == 0)
		i++;
	if (list->line[i - 1] == LABEL_CHAR)
	{
		get_label_name(list, i);
		list->line_char = i;
		while (list->line[list->line_char] &&
			ft_isspace(list->line[list->line_char]) == 1)
			list->line_char++;
		if (list->line[list->line_char] == '\0')
		{
			list->new_node = 1;
			return ;
		}
		else
			return (check_sort(list, new, i + 1));
	}
	else
		check_operation(list, new, i);
}
