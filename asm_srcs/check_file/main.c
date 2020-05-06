/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 15:46:14 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/05/06 10:03:31 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief Here it malloc the hash table for valid operations
**
** @return uint64_t*  it returns the hash table filled in
**
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
** @brief:	init the main store data structure
** 			also it makes his own hash table;
**
** @param	list = the container where we store all our information
** @param	list->name = is the name of the champion
** @param	list->comment = is the comment
** @param	list->info = contain a struct list with the operations
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_= char keep track the index accesed in line.
** @param	list->line_number = is the line number readed from file.
** @param	list->hash_table = is a hash table of possible operations.
** @param	list->new_node = is to keep track if the new node is totally filled
**			or not.
** @param	list->labels = is a list of hashes from labels.
**			within there is a list of the actually label as string.
** @param	list->total_bytes = keeps track of the amount of bytes
** @param	list->cn_size = is needed to determine if its a comment or a name
*/

static void		init_func_list(t_func_list *list)
{
	list->name = NULL;
	list->comment = NULL;
	list->line = NULL;
	list->info = NULL;
	list->line_char = -1;
	list->line_number = 0;
	list->hash_table = make_hash_table();
	list->new_node = 0;
	list->labels = NULL;
	list->cn_size = 0;
	list->total_bytes = 0;
	if (list->hash_table == NULL)
		error_message(list, 1, 1, 0);
}

/*
** @brief start of our program
*/

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
	if (list.info == NULL)
		error_message(&list, 2, 2, 0);
	create_cor_file(argv[i - 1], &list);
	free_func(&list);
	return (0);
}
