/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 10:02:48 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/17 08:12:16 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_direction(t_func_list *list)
{
	t_direction *iter;
	t_direction *next;
	int			i;

	i = 0;
	iter = list->info;
	next = NULL;
	while (iter != NULL)
	{
		next = iter->next;
		while (i < 3)
		{
			if (iter->arg_str[i] != NULL)
				ft_memdel((void **)iter->arg_str[i]);
			i++;
		}
		ft_memdel((void **)iter->arg_str);
		ft_memdel((void **)iter->arg_num);
		if (iter->label != NULL)
			ft_memdel((void **)iter->label);
		iter = next;
	}
}

void	free_func(t_func_list *list)
{
	if (list->name != NULL)
		ft_memdel((void**)list->name); //ft_memdel freed current data and sets it to NULL
	if (list->comment != NULL)
		ft_memdel((void**)list->comment);
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

/*
** @brief
**
** @param fd_name = name of 2d char array containing splitted stings
**
** free_split frees every element in 2d array by iterating through it
*/

void	free_split(char **fd_name)
{
	int	index;

	index = 0;
	while (fd_name[index] != NULL)
	{
		free(fd_name[index]);
		index++;
	}
	free(fd_name);
	fd_name = NULL;
}
