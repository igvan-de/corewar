/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 10:02:48 by mlokhors      #+#    #+#                 */
/*   Updated: 2020/05/06 09:58:51 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	@brief	:	free label hash list
**
**	@param	label	:	ptr to label list
**
**	free_cmp_label frees the label hash and node
**	for each node of the label list.
*/

static	void	free_cmp_label(t_labels **label)
{
	t_labels *ptr;
	t_labels *ptr2;

	ptr = *label;
	ptr2 = NULL;
	while (ptr != NULL)
	{
		ptr2 = ptr->next;
		if (ptr->label != NULL)
			free(ptr->label);
		free(ptr);
		ptr = ptr2;
	}
}

/*
**	@brief	:	free label data structures
**
**	@param	list	:	main data structure
**
**	free_hash_label frees the first level of
**	label data nodes and calls free_cmp_label for
**	each node.
*/

static	void	free_hash_labels(t_func_list *list)
{
	t_hash_label *ptr;
	t_hash_label *ptr2;

	ptr = list->labels;
	ptr2 = NULL;
	while (ptr != NULL)
	{
		ptr2 = ptr->next;
		if (ptr->label != NULL)
			free_cmp_label(&ptr->label);
		free(ptr);
		ptr = ptr2;
	}
}

/*
**	@brief	:	free operation data structures
**
**	@param	list	:	main data structure
**
**	free_direction frees the list of nodes
**	that contain the data related to the operations.
*/

static	void	free_direction(t_func_list *list)
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
		free(iter);
		iter = next;
	}
}

/*
**	@brief	:	free all remaining data structures
**
**	@param	list	:	main data structure
**
**	after asm has executed successfully, free_func is called
**	to free all remaining data structures.
*/

void			free_func(t_func_list *list)
{
	if (list->name != NULL)
		ft_memdel((void**)&list->name);
	if (list->comment != NULL)
		ft_memdel((void**)&list->comment);
	if (list->line != NULL)
		ft_memdel((void**)&list->line);
	if (list->hash_table != NULL)
		ft_memdel((void**)&list->hash_table);
	if (list->info != NULL)
		free_direction(list);
	list->info = NULL;
	if (list->labels != NULL)
		free_hash_labels(list);
	list->labels = NULL;
}
