/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash_label.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:04:13 by mark           #+#    #+#                */
/*   Updated: 2020/04/03 04:39:19 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"



void	add_new_hash(t_func_list *list, char *label, int index, uint64_t hash)
{
	t_hash_label *ptr;

	ptr = list->labels;
	while (ptr)
		ptr = ptr->next;
	ptr->next = ft_memalloc(sizeof(t_hash_label));
	if (ptr->next == NULL)
		error_message(list, 73 ,0, 7);
	ptr = ptr->next;
	ptr->hash_label = hash;
	ptr->label = ft_memalloc(sizeof(t_labels));
	if (ptr->label == NULL)
		error_message(list, 74, 0, 7);
	ptr->label->index = index;
	ptr->label->label = ft_strdup(label);

}

void	search_ex_hash(t_func_list *list, char *label, int index, uint64_t hash)
{
	t_hash_label *ptr;
	t_labels *labels;

	labels = NULL;
	ptr = list->labels;
	while (ptr)
	{
		if (hash == ptr->hash_label)
		{
			labels = ptr->label;
			while (labels)
				labels = labels->next;
			labels->next = ft_memalloc(sizeof(t_labels));
			if (labels->next == NULL)
				error_message(list, 72, 0, 7);
			labels = labels->next;
			labels->label = ft_strdup(label);
			labels->index = index;
		}
		ptr = ptr->next;
	}
	add_new_hash(list, label, index, hash);
}

void	add_to_hash(t_func_list *list, char *label, int index)
{
	uint64_t hash;

	hash = calc_hash(label, ft_strlen(label));
	if (list->labels == NULL)
	{
		list->labels = ft_memalloc(sizeof(t_hash_label));
		if (list->labels == NULL)
			error_message(list, 70, 0, 7);
		list->labels->hash_label = hash;
		list->labels->label = ft_memalloc(sizeof(t_labels));
		if (list->labels->label == NULL)
			error_message(list, 71, 0, 7);
		list->labels->label->label = ft_strdup(label);
		list->labels->label->index = index;
	}
	else
		search_ex_hash(list, label, index, hash);	
}