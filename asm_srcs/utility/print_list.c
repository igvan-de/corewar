/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 15:46:14 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/15 12:13:27 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		print_encode(t_direction *ptr)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (ptr->encode & 1 << (7 - i))
			ft_printf("1");
		else
			ft_printf("0");
		i++;
	}
	ft_printf("\n");
}

static	void	print_arg_vals(t_direction *ptr)
{
	int i;

	i = 0;
	while (i < 3)
	{
		ft_printf("arg_num %d\n", ptr->arg_num[i]);
		i++;
	}
}

static	void	print_labels(t_hash_label *a)
{
	t_labels *b;

	ft_printf("\n");
	while (a)
	{
		ft_printf("hash %d\n", a->hash_label);
		b = a->label;
		while (b)
		{
			ft_printf("  label %s index %d \n", b->label, b->index);
			b = b->next;
		}
		a = a->next;
	}
	ft_printf("\n");
}

/*
**	@brief	:	print contents of the func_list to stdout
**
**	@param	list	: main data structure
*/

void			print_list(t_func_list *list)
{
	t_direction		*ptr;

	ptr = list->info;
	if (ptr->next == NULL)
		ft_printf("fuck]\n");
	ft_printf("total %d\n", list->total_bytes);
	while (ptr)
	{
		ft_printf("index:%d\n", ptr->byte_index);
		ft_printf("op_code %d\nbyte_size %d\n", ptr->op_code, ptr->byte_size);
		print_encode(ptr);
		print_arg_vals(ptr);
		ptr = ptr->next;
	}
	print_labels(list->labels);
}
