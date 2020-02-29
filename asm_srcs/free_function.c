/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 10:02:48 by mlokhors       #+#    #+#                */
/*   Updated: 2020/02/29 10:06:27 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_direction(t_func_list *list)
{
	t_direction *iter;
	t_direction *next;

	iter = list->info;
	next = NULL;

	while (iter)
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
	{
		free(list->name);
		list->name = NULL;
	}
	if (list->comment != NULL)
	{
		free(list->name);
		list->comment = NULL;
	}
	if (list->info != NULL)
		free_direction(list);
	if (list->hash_table != NULL)
		free(list->hash_table);
}

void	free_all_but_hash(t_func_list *list)
{
	if (list->name != NULL)
	{
		free(list->name);
		list->name = NULL;
	}
	if (list->comment != NULL)
	{
		free(list->name);
		list->comment = NULL;
	}
	if (list->info != NULL)
	{
		free_direction(list);
		list->info = NULL;
	}
}