/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_t_reg.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:13:08 by mark          #+#    #+#                 */
/*   Updated: 2020/04/22 19:32:38 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** process T_REG. it adds the bytes to the total and node.
** get the number and insert the encode byte.
*/

void		process_t_reg(t_func_list *list, t_direction *new, int arg)
{
	int converted;

	list->total_bytes += 1;
	new->byte_size += 1;
	list->line_char++;
	if (!(list->line[list->line_char] >= '0' &&
		list->line[list->line_char] <= '9'))
		error_message(list, 99, 0, 9);
	converted = pm_atoi(list);
	insert_encode(new, arg, REG_CODE);
	new->arg_num[arg] = converted;
}
