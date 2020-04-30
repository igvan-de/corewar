/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_to_hash.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:04:13 by mark          #+#    #+#                 */
/*   Updated: 2020/04/30 10:39:05 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** So All what this file does is that it makes a hash from the label
** if it does exist it does nothing
** if it doesnt exist it will make a new node.
** if the hash exist but it isnt the same then the actually string
** it will compare with the nexts sub node.
** if there is none it will make a new sub node within the hash node
*/

static bool	check_label_node(t_func_list *list, t_labels **last,
		t_labels **ptr, char *label)
{
	t_labels *iter;
	t_labels *new;

	new = NULL;
	iter = *last;
	if (!iter)
		error_message(list, 72, 0, 7);
	while (iter)
	{
		if (ft_strcmp(iter->label, label) == 0)
		{
			return (false);
		}
		iter = iter->next;
	}
	new = ft_memalloc(sizeof(t_labels));
	if (new == NULL)
		error_message(list, 72, 0, 7);
	(*ptr) = new;
	iter->next = new;
	return (true);
}

static void	add_hash_label_node(t_func_list *list, t_hash_label **ptr,
		uint64_t hash)
{
	*ptr = ft_memalloc(sizeof(t_hash_label));
	if (*ptr == NULL)
		error_message(list, 70, 0, 7);
	(*ptr)->hash_label = hash;
	(*ptr)->label = ft_memalloc(sizeof(t_labels));
	if ((*ptr)->label == NULL)
		error_message(list, 71, 0, 7);
}

static void	search_ex_hash(t_func_list *list, char *label, uint64_t hash)
{
	t_hash_label	*ptr;
	t_labels		*table;

	table = NULL;
	ptr = list->labels;
	while (ptr)
	{
		if (hash == ptr->hash_label)
		{
			if (check_label_node(list, &(ptr->label), &table, label) == true) //changed boolean value, need to check if code is still working good
			{
				table->label = ft_strdup(label);
				table->index = list->total_bytes;
			}
			return ;
		}
		if (ptr->next == NULL)
			break ;
		ptr = ptr->next;
	}
	add_hash_label_node(list, &ptr->next, hash);
	ptr->next->hash_label = hash;
	ptr->next->label->label = ft_strdup(label);
	ptr->next->label->index = list->total_bytes;
}

void		add_to_hash(t_func_list *list, char *label)
{
	uint64_t hash;

	hash = calc_hash(label, ft_strlen(label));
	if (list->labels == NULL)
	{
		add_hash_label_node(list, &list->labels, hash);
		list->labels->hash_label = hash;
		list->labels->label->label = ft_strdup(label);
		list->labels->label->index = list->total_bytes;
	}
	else
		search_ex_hash(list, label, hash);
}
