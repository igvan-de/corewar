/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_t_reg.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:13:08 by mark          #+#    #+#                 */
/*   Updated: 2020/06/05 17:42:13 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief	process t_reg type argument
**
** @param	list = the container where we store all our information
** @param	list->line_char = keep track the index accesed in line.
** @param	list->total_bytes = keeps track of the amount of bytes
** @param	new = memory adress from a new or existing list.
**			it always has the last node in the list
**			this list contains all the information for a operation
** @param	new->byte_size = size of the operation
** @param	new->arg_num = an array of ints to store operation arguments
** @param	arg = which argument of the operation it is
**
** adjust the byte size of the operation node and the total bytes
** it also insert the encode byte
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
	if (converted < 0 || converted > 99)
		error_message(list, 90, 1, 9);
	check_between(list, 98, 0, 9);
	insert_encode(new, arg, REG_CODE);
	new->arg_num[arg] = converted;
}
