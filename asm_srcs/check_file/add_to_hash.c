/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_to_hash.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:04:13 by mark          #+#    #+#                 */
/*   Updated: 2020/05/04 02:44:50 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief	search if the label already exist
**
** @param	list = the container where we store all our information
** @param	node = hash node that has the same hash of label
** @param	ptr = pointer to the new node of s_label list.
**			this list is stored inside of a s_hash_label
** @param	label = label name
**
** allocated a new node to store a hash.
** it will also allocate a new list to store the label in that node
*/

static bool	check_label_node(t_func_list *list, t_labels **node,
		t_labels **ptr, char *label)
{
	t_labels *iter;
	t_labels *new;

	new = NULL;
	iter = *node;
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

/*
** @brief	allocated a new node to store a hash.
**
** @param	list = the container where we store all our information
** @param	ptr = pointer to list->labels or
**			the last node of list->labels
** @param	hash = hash calculated from a label
**
** allocated a new node to store a hash.
** it will also allocate a new list to store the label in that node
*/

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

/*
** @brief	search if the hash already exist
**
** @param	list = the container where we store all our information
** @param	label = label name
** @param	list->labels = is a list of hashes from labels.
**			within there is a list of the actually label as string.
** @param	list->labels->label = stores the index and the actually
**			label as string
** @param	hash = hash calculated from a label
**
** this search if the hash generate from the string already exist
** if has already exist it will be added inside the list of that hash
** else it will make a new node of hash list and fill that in
*/

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
			if (check_label_node(list, &(ptr->label), &table, label) == true)
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

/*
** @brief	create the hashes of labels list
**
** @param	list = the container where we store all our information
** @param	label = label name
** @param	list->labels = is a list of hashes from labels.
**			within there is a list of the actually label as string.
** @param	list->labels->label stores the index and the actually
**			label as string
*/

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
