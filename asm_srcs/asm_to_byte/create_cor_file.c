/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cor_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:27:18 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/09 14:50:45 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

/*
** magic_header we always start with placing the magic_header in .cor file
** and then continueing to convert name, comment executable code into .cor file
*/

// void	magic_header(t_func_list *list)
// {

// }

/*
** @brief Get the name object
**
** @param argv = is the argument needed to get the name
** @return char* = returns the correct .cor file name
**
** splits the string (argv) by / if its in the string and with .
** so we get the correct file name, then with strjoin we join the name with .cor
** the create the correct .cor file name and save it in fd_name which we return
*/

static char *get_name(char *argv)
{
	char	*fd_name;
	char	**name;
	int		i;

	i = 0;
	name = ft_strsplit(argv, '/');
	while (name[i] != NULL)
		i++;
	fd_name = ft_strdup(name[i - 1]);
	free_split(name);
	name = ft_strsplit(fd_name, '.');
	free(fd_name);
	fd_name = ft_strjoin(name[NAME], ".cor");
	ft_printf("name = %s\n", fd_name); //is to test if filename is correct, need to remove later!
	return (fd_name);
}

/*
** @brief Create a cor file object
**
** @param argv = is the string of the last argument
** @param list = is structure with all needed data in it
**
** create_cor_file is the main for creating a .cor file
** we get the correct .cor name by the return value of get_name function and save it in fd_name
*/

void	create_cor_file(char *argv, t_func_list *list)
{
	int		fd;
	char	*fd_name;
	t_func_list *test;

	test = list;
	fd_name = get_name(argv);
	fd = open(fd_name, O_CREAT | O_WRONLY, 0640);
	/*functions for precossing data into file*/
	free(fd_name);
}
