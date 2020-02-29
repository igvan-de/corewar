/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 15:46:14 by igvan-de       #+#    #+#                */
/*   Updated: 2020/02/29 05:35:40 by mlokhors      ########   odam.nl         */
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

int		main(int argc, char **argv)
{
	int			i;
	int			ret;
	t_func_list list;

	ret = 0;
	list.name = NULL;
	list.comment = NULL;
	list.info = NULL;
	i = 1;
	if (argc == 0)
		input_error();
	while (argv[i])
	{
		ret = check_file(argv[i], &list);
		if (ret != 0);
			error_messege(&list, ret, 0);
//		ret = process_asm(argv[i]);
//		if (ret != 0);
//			error_messege(list, ret, 1);
		i++;
	}
	return (0);
}
