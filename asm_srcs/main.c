/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 15:46:14 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/05 13:03:43 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
// 1 file of meerdere
/*

char	*ft_strndup(const char *s1, int leng)
{
	int		i;
	int		length;
	char	*dest;

	i = 0;
	while (s1[i])
		i++;
	if (i > length)
		i = length;
	dest = (char*)ft_memalloc(sizeof(char) * i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && i < leng)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_func_list	*add_func_node()
{
	t_func_list *new;

	new = (t_func_list *)malloc(sizeof(t_func_list));
	if (!new)
		return (NULL);
	new->n = NULL;
	new->func_name = NULL;
	new->next = NULL;
}

char	*trim_name(char *file_name)
{
	int length;

	length = ft_strlen(file_name);
	length -= 2;
	return(ft_strndup(file_name, length));
}

void	process_asm(char *file_name)
{
	int		fd;
	char	*cor_name;
	int 	len;
	cor_name = ft_strjoin(trim_name(file_name), ".cor");
	if (cor_name == NULL)
		failed_malloc_process();
	fd = open(cor_name, O_WRONLY | O_CREAT | O_TRUNC, 644);
}
*/
/*
**	compiling for each file
**	need to rework on it since the program will stop if 1 file is not correct
*/

static void	print_array(int *array)
{
	int i;

	i = 0;
	while (i < 16)
	{
		printf("%d\n", array[i]);
		i++;
	}
}

static int	make_hash(char *operation)
{
	int total;
	int i;

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

static int	*make_hash_table(void)
{
	int			*table;
	int			i;
	static char operation[16][6] = {"live", "ld", "st", "add", "sub", "and",
	"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
	};

	i = 0;
	table = (int *)ft_memmalloc(sizeof(int) * 16);
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

static void	init_func_list(t_func_list *list)
{
	list->hash_table = make_hash_table();
	if (list->hash_table == NULL)
		error_message(&list, 13, 2);
}

int			main(int argc, char **argv)
{
	int			i;
	int			ret;
	t_func_list list;

	init_func_list(&list);
	i = 1;
	if (argc == 0)
		input_error();
	while (argv[i])
	{
		check_file(argv[i], &list);
		free_all_but_hash(&list);
		i++;
	}
	free(list.hash_table);
	return (0);
}
