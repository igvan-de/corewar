/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 10:02:48 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/06 13:00:48 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_direction(t_func_list *list)
{
	t_direction *iter;
	t_direction *next;

	iter = list->info;
	next = NULL;
	while (iter != NULL)
	{
		next = iter->next;
		if (iter->label != NULL)
			free(iter->label);
		if (iter->target_label != NULL)
			free(iter->target_label);
		iter = next;
	}
}

void	free_func_error(t_func_list *list)
{
	if (list->name != NULL)
		ft_memdel((void**)list->name); //ft_memdel freed current data and sets it to NULL
	if (list->comment != NULL)
		ft_memdel((void**)list->comment);
	if (list->info != NULL)
		free_direction(list);
	if (list->hash_table != NULL)
		free(list->hash_table);
}

void	free_all_but_hash(t_func_list *list)
{
	if (list->name != NULL)
		ft_memdel((void**)list->name);
	if (list->comment != NULL)
		ft_memdel((void**)list->comment);
	if (list->info != NULL)
	{
		free_direction(list);
		list->info = NULL;
	}
}
