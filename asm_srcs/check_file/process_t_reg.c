/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_t_reg.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:13:08 by mark          #+#    #+#                 */
/*   Updated: 2020/04/09 02:55:10 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		process_t_reg(t_func_list *list, t_direction *new,int arg)
{
	int converted;

	list->total_bytes += 1;
	new->byte_size += 1;
	list->line_char++;
	if (!(list->line[list->line_char] >= '0' && list->line[list->line_char] <= '9'))
		error_message(list, 99, 0, 9);
	converted = pm_atoi(list);
	if (converted <= 0 || converted > 16)
		error_message(list, 90, 1, 9);
	if (list->line[list->line_char] != SEPARATOR_CHAR && list->line[list->line_char] != '\0' &&
		ft_isspace(list->line[list->line_char]) == 1)
		error_message(list, 98, 0, 9);
	insert_encode(new, arg, REG_CODE);
	new->arg_num[arg] = converted;
}