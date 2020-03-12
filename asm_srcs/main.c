/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 15:46:14 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/08 16:09:23 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** the function that actually make the hash
*/

int		make_hash(char *operation)
{
	int			total;
	int			i;

	i = 0;
	total = 0;
	while (*operation != '\0')
	{
		total += till_power(*operation, i);
		operation++;
		i++;
	}
	return (total);
}

/*
** make the hash table
*/

int		*make_hash_table(void)
{
	int			*table;
	int			i;
	static char	operation[16][6] = {"live", "ld", "st", "add", "sub", "and",
	"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
	};

	i = 0;
	table = (int *)ft_memalloc(sizeof(int) * 16);
	if (!table)
		return (NULL);
	ft_bzero(table, 16 * (sizeof(int)));
	while (i < 16)
	{
		table[i] = make_hash(operation[i]);
		i++;
	}
	return (table);
}

/*
**		init the main store data structure
*/

void		init_func_list(t_func_list *list)
{
	list->name = NULL;
	list->comment = NULL;
	list->info = NULL;
	list->line_char = -1;
	list->line_number = 0;
	list->hash_table = make_hash_table();
	if (list->hash_table == NULL)
		error_message(list, 0, 0);
}

int			main(int argc, char **argv)
{
	int			i;
	t_func_list	list;

	init_func_list(&list);
	i = 0;
	if (argc == 1)
		error_message(&list, 1, 1);
	while (argv[i] != NULL)
		i++;
	// check_file(argv[argc], &list);
	// process_asm(argv[i - 1]);
	create_cor_file(argv[i - 1], &list);
	free_all_but_hash(&list);
	return (0);
}
