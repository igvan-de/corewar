/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_t_ind.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:13:13 by mark          #+#    #+#                 */
/*   Updated: 2020/04/15 02:48:37 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** process T_IND. it adds the bytes to the total and node.
** get the number and insert the encode byte.
*/

void		process_t_ind(t_func_list *list, t_direction *new, int arg)
{
	int converted;

	list->total_bytes += 2;
	new->byte_size += 2;
	converted = pm_atoi(list);
	if (list->line[list->line_char] != SEPARATOR_CHAR &&
		list->line[list->line_char] != '\0' &&
		ft_isspace(list->line[list->line_char]) == 1)
		error_message(list, 100, 0, 10);
	insert_encode(new, arg, IND_CODE);
	new->arg_num[arg] = converted;
}
