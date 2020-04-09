/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_instruction_node.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 11:09:42 by mlokhors      #+#    #+#                 */
/*   Updated: 2020/04/09 03:04:38 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** adds a node to the list and set them to 0
*/

void	add_back_end(t_direction **info, t_direction *new)
{
	t_direction *tmp;

	tmp = *info;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	init_args(t_func_list *list, t_direction **iter)
{
	(*iter)->arg_str = ft_memalloc(sizeof(char *) * 3);
	if ((*iter)->arg_str == NULL)
		error_message(list, 51, 0, 5);
	(*iter)->arg_num = ft_memalloc(sizeof(int) * 3);
	if ((*iter)->arg_num == NULL)
		error_message(list, 52, 0, 5);
}

void	add_instruction_node(t_func_list *list, t_direction **info,
		t_direction **pointer)
{
	t_direction *new;

	*pointer = NULL;
	new = (t_direction *)ft_memalloc(sizeof(t_direction));
	if (!new)
		error_message(list, 50, 0, 5);
	init_args(list, &new);
	new->byte_index = list->total_bytes;
	if (!*info)
		*info = new;
	else
		add_back_end(info, new);
	*pointer = new;
}
