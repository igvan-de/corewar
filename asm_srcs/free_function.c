/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 10:02:48 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/06 13:34:02 by mlokhors      ########   odam.nl         */
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
		if (iter->arg_1 != NULL)
			ft_memdel((void **)iter->arg_1);
		if (iter->arg_2 != NULL)
			ft_memdel((void **)iter->arg_2);
		if (iter->arg_3 != NULL)
			ft_memdel((void **)iter->arg_3);
		if (iter->label != NULL)
			ft_memdel((void **)iter->label);
		iter = next;
	}
}

void	free_func(t_func_list *list)
{
	if (list->name != NULL)
		ft_memdel((void **)list->name);
	if (list->comment != NULL)
		ft_memdel((void **)list->comment);
	if (list->info != NULL)
		free_direction(list);
	if (list->hash_table != NULL)
		ft_memdel((void **)list->hash_table);
}
