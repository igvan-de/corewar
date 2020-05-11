/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_instruction_node.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 11:09:42 by mlokhors      #+#    #+#                 */
/*   Updated: 2020/05/04 02:18:07 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief	adds new node to the end of operation list
**
** @param	list = the container where we store all our information
** @param	new = pointer to the last new node of the operation list
*/

static void	add_back_end(t_direction **info, t_direction *new)
{
	t_direction *tmp;

	tmp = *info;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/*
** @brief	init array needed to store operation arguments
**
** @param	list = the container where we store all our information
** @param	new = pointer to the last new node of the operation list
**
** init the arrays needed to store the arguments.
** it will keep making an array of 3 for strings and number
** even if there is only 1 argument. the reason is,
** dont we dont have to reallocate to make the size bigger
*/

static void	init_args(t_func_list *list, t_direction **new)
{
	(*new)->arg_str = ft_memalloc(sizeof(char *) * 3);
	if ((*new)->arg_str == NULL)
		error_message(list, 51, 0, 5);
	(*new)->arg_num = ft_memalloc(sizeof(int) * 3);
	if ((*new)->arg_num == NULL)
		error_message(list, 52, 0, 5);
}

/*
** @brief	makes a new list for operation if does not exist
**
** @param	list = the container where we store all our information
** @param	info = pointer to the list struct for operation list
** @param	pointer = pointer to the last node of the operation list
*/

void		add_instruction_node(t_func_list *list, t_direction **info,
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
