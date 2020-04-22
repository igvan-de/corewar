/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_t_ind.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:13:13 by mark          #+#    #+#                 */
/*   Updated: 2020/04/22 19:34:44 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** process T_IND. it adds the bytes to the total and node.
** get the number and insert the encode byte.
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

void		process_t_ind(t_func_list *list, t_direction *new, int arg)
{
	int converted;

	list->total_bytes += 2;
	new->byte_size += 2;
	converted = pm_atoi(list);
	insert_encode(new, arg, IND_CODE);
	if (list->line[list->line_char] == LABEL_CHAR)
	{
		new->label_in_op = 1;
		get_label_op(list, new, arg);
		return ;
	}
	if (list->line[list->line_char] != SEPARATOR_CHAR &&
		list->line[list->line_char] != '\0' &&
		ft_isspace(list->line[list->line_char]) == 1 &&
		list->line[list->line_char] != COMMENT_CHAR)
		error_message(list, 100, 0, 10);
	new->arg_num[arg] = converted;
}
