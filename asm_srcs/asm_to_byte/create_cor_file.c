/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cor_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:27:18 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/07 18:03:11 by igvan-de      ########   odam.nl         */
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
** create_cor_file is the main for creating a .cor file
** it receives argv to give the .cor file the correct name
** and t_func_list with all data of given file needed to place in .cor file
*/
#include <stdio.h>

void	create_cor_file(char *argv, t_func_list *list)
{
	int		fd;
	char	*fd_name;
	t_func_list *test;

	test = list;
	fd_name = ft_strjoin(argv, ".cor");
	printf("name = %s\n", fd_name);
	/*need function that checks only the name of champin and change it into .cor file*/
	fd = open(fd_name, O_CREAT | O_WRONLY, 0640);
}
