/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 15:46:14 by igvan-de       #+#    #+#                */
/*   Updated: 2020/02/20 13:47:52 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
// 1 file of meerdere


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
	
	cor_name = trim_name(file_name);
	if (!cor_name)
		failed_malloc_process();
	fd = ();
}
/*
void	check_file(char *file_name, int *name_len)
{
	if (check_correct_file(file_name, name_len) == 1)
		input_not_asm();
	if (check_asm_file(file_name) == 1)
		input_bad_asm();
}
*/
int	main(int argc, char **argv)
{
	int	i;
	int name_len;

	name_len = 0;
	i = 1;
	if (argc == 0)
		input_error();
	while (argv[i])
	{
		name_len = 0;
//		check_file(argv[i], &name_len);
		process_asm(argv[i]);
		i++;
	}
	return (0);
}
