/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 10:02:48 by mlokhors      #+#    #+#                 */
/*   Updated: 2020/04/09 04:04:00 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_cmp_label(t_labels **label)
{
	t_labels *ptr;
	t_labels *ptr2;

	ptr = *label;
	ptr2 = NULL;
	while (ptr != NULL)
	{
		ptr2 = ptr->next;
		if (ptr->label != NULL)
			ft_memdel((void **)&ptr);
		ptr = ptr2;
	}
}

void	free_hash_labels(t_func_list *list)
{
	t_hash_label *ptr;
	t_hash_label *ptr2;

	ptr = list->labels;
	ptr2 = NULL;
	while (ptr != NULL)
	{
		ptr2 = ptr->next;
		if (ptr->label != NULL)
		{
			free_cmp_label(&ptr->label);
			ft_memdel((void **)&ptr);
		}
		ptr = ptr2;
	}
}

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
		i = 0;
		next = iter->next;
		while (i < 3)
		{
			if (iter->arg_str[i] != NULL)
				ft_memdel((void **)&iter->arg_str[i]);
			i++;
		}
		ft_memdel((void **)&iter->arg_str);
		ft_memdel((void **)&iter->arg_num);
		iter = next;
	}
}

void	free_func(t_func_list *list)
{
	if (list->name != NULL)
		ft_memdel((void**)&list->name);
	if (list->comment != NULL)
		ft_memdel((void**)&list->comment);
	if (list->hash_table != NULL)
		ft_memdel((void**)&list->hash_table);
	if (list->info != NULL)
		free_direction(list);
	if (list->labels != NULL)
		free_hash_labels(list);
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
