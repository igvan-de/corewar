/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_t_ind.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:13:13 by mark           #+#    #+#                */
/*   Updated: 2020/04/03 03:33:57 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		process_t_ind(t_func_list *list, t_direction *new, int arg)
{
	int converted;

	list->total_bytes += 2;
	new->byte_size += 2;
	converted = pm_atoi(list);
	if (list->line[list->line_char] != SEPARATOR_CHAR && list->line[list->line_char] != '\0' &&
		ft_isspace(list->line[list->line_char]) == 1)
		error_message(list, 100, 0, 10);
	insert_encode(new, arg, IND_CODE);
	new->arg_num[arg] = converted;
}