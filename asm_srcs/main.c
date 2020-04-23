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

static void		init_func_list(t_func_list *list)
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

int				main(int argc, char **argv)
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
	create_cor_file(argv[i - 1], &list);
	return (0);
}
