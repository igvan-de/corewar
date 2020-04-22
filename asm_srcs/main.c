/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 15:46:14 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/15 12:13:27 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
// remove this test when final

/*
static void print_list(t_func_list *list)
{
	t_direction *ptr;
	t_hash_label *a;
	t_labels *b;
	int i = 0;

	a = NULL;
	b = NULL;
	ptr = list->info;
	if (ptr->next == NULL)
		printf("fuck]\n");
	ft_printf("total %d\n", list->total_bytes);
	while (ptr)
	{
		i = 0;
		ft_printf("index:%d\n", ptr->byte_index);
		ft_printf("op_code %d\nbyte_size %d\n", ptr->op_code, ptr->byte_size);
		while (i < 8)
		{
			if (ptr->encode & 1 << (7 - i))
				ft_printf("1");
			else
				ft_printf("0");
			i++;
		}
		ft_printf("\n");
		i = 0;
		while (i < 3)
		{
			ft_printf("arg_num %d\n", ptr->arg_num[i]);
			i++;
		}
		ptr = ptr->next;
	}
	a = list->labels;
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

*/

/*
** Here it malloc the hash table for valid operations
** it will transform them into a hash.
** its based on the Fowler–Noll–Vo hash function
*/

static uint64_t	*make_hash_table(void)
{
	uint64_t	*table;
	int			i;
	static char	operation[16][6] = {"live", "ld", "st", "add", "sub", "and",
	"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
	};

	i = 0;
	table = (uint64_t *)ft_memalloc(sizeof(uint64_t) * 16);
	if (!table)
		return (NULL);
	ft_bzero(table, 16 * (sizeof(uint64_t)));
	while (i < 16)
	{
		table[i] = calc_hash(operation[i], ft_strlen(operation[i]));
		i++;
	}
	return (table);
}

/*
**		init the main store data structure
**		also it makes his own hash table;
*/

static void	init_func_list(t_func_list *list)
{
	list->name = NULL;
	list->comment = NULL;
	list->info = NULL;
	list->line_char = -1;
	list->line_number = 0;
	list->hash_table = make_hash_table();
	list->new_node = 0;
	list->labels = NULL;
	if (list->hash_table == NULL)
		error_message(list, 1, 1, 0);
}

int			main(int argc, char **argv)
{
	int			i;
	t_func_list	list;

	init_func_list(&list);
	i = 0;
	if (argc == 1)
		error_message(&list, 0, 0, 0);
	while (argv[i] != NULL)
		i++;
	check_n_process(argv[argc - 1], &list);
//	print_list(&list);
	// process_asm(argv[i - 1]);
	create_cor_file(argv[i - 1], &list);
//	free_all_but_hash(&list);
	return (0);
}
