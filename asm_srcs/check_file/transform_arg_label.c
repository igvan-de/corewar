/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform_arg_label.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 03:15:15 by mark          #+#    #+#                 */
/*   Updated: 2020/04/09 03:46:46 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	cmp_str_hash(t_func_list *list, t_labels *h_label, t_direction **iter, int i)
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
	error_message(list, 0, 0, 0);
}

void	conv_search_hash(t_func_list *list, t_direction **iter , int i)
{
	uint64_t hash;
	t_hash_label *table;

	hash = calc_hash((*iter)->arg_str[i], ft_strlen((*iter)->arg_str[i]));
	table = list->labels;
	while (table)
	{
		if (table->hash_label == hash)
			return (cmp_str_hash(list, table->label, iter, i));
		table = table->next;
	}
	error_message(list, 0 , 0, 0);
}

void 	transfrom_arg_label(t_func_list *list)
{
	t_direction *iter;
	int i;

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
				return ;
			}
			i++;
		}
		iter = iter->next;
	}
}