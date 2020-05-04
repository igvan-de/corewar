/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform_label.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 03:15:15 by mark          #+#    #+#                 */
/*   Updated: 2020/05/04 04:58:30 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief	search in the hash node for the label name
**
** @param	h_label is the list within the hash node with labels name
** @param	iter = contain a struct list with the operations
** @param	i = iteration
**
** here we actually do the converation
** its based on the index from the beginning when this label occurs
** each operation has a size. label point to the beginning of an operation
*/

static void	cmp_str_hash(t_func_list *list, t_labels *h_label,
			t_direction **iter, int i)
{
	t_labels *l_iter;

	l_iter = h_label;
	while (l_iter)
	{
		if (ft_strcmp(l_iter->label, (*iter)->arg_str[i]) == 0)
		{
			(*iter)->arg_num[i] = l_iter->index - (*iter)->byte_index;
			return ;
		}
		l_iter = l_iter->next;
	}
	error_message(list, 121, 1, 13);
}

/*
** @brief	transform argument labels into hash and search for hash in
**			list->labels
**
** @param	list = the container where we store all our information
** @param	iter = contain a struct list with the operations
** @param	i = iteration
**
** here the str is being transformed into hash
** it will search for the correspoding existing hash
** if there is no corresponding hash then the label isnt valid
** this is to avoid collision with the hash function
*/

static void	conv_search_hash(t_func_list *list, t_direction **iter, int i)
{
	uint64_t		hash;
	t_hash_label	*table;

	hash = calc_hash((*iter)->arg_str[i], ft_strlen((*iter)->arg_str[i]));
	table = list->labels;
	while (table)
	{
		if (table->hash_label == hash)
			return (cmp_str_hash(list, table->label, iter, i));
		table = table->next;
	}
	error_message(list, 120, 0, 12);
}

/*
** @brief	transform label strings into string based on index
**
** @param	list = the container where we store all our information
** @param	list->info = contain a struct list with the operations
** @param	iter->arg_str = node of list->info that stores a label given as
**			a type argument
**
** search for each node that all arg_str are NULL
** if it isnt not then it means there is a label that must be converted
*/

void		transform_label(t_func_list *list)
{
	t_direction *iter;
	int			i;

	i = 0;
	iter = list->info;
	while (iter)
	{
		i = 0;
		while (i < 3)
		{
			if (iter->arg_str[i] != NULL)
			{
				conv_search_hash(list, &iter, i);
				ft_memdel((void**)&iter->arg_str[i]);
			}
			i++;
		}
		iter = iter->next;
	}
}
