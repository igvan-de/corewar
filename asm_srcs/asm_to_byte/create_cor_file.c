/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cor_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:27:18 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/11 10:02:19 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

/*
** @brief gets the right file name
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
	char	**name;
	char	*fd_name;
	int		index;

	index = 0;
	name = ft_strsplit(argv, '/');
	while (name[index] != NULL)
		index++;
	fd_name = ft_strdup(name[index - 1]);
	free_split(name);
	name = ft_strsplit(fd_name, '.');
	free(fd_name);
	fd_name = ft_strjoin(name[NAME], ".cor");
	/*need to test more, unit_test!*/
	return (fd_name);
}

/*
** @brief creates cor file
**
** @param argv = is the string of the last argument
** @param list = is structure with all needed data in it
**
** create_cor_file is the main for creating a .cor file
** we get the correct .cor name by the return value of get_name function and save it in fd_name
*/

void	create_cor_file(char *argv, t_func_list *list)
{
	char	*fd_name;
	int		fd;

	list->name = "badman";
	list->comment = "this city needs me";
	fd_name = get_name(argv);
	fd = open(fd_name, O_CREAT | O_WRONLY, 0640);
	write_cor_file(fd, list);
	free(fd_name);
}
