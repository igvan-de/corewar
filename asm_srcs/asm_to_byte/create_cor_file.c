/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cor_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:27:18 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/15 11:00:51 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	@brief: get the right file name
**
** @param argv = is the argument needed to get the name
** @return char* = returns the correct .cor file name
**
** splits the string (argv) by / if its in the string and with .
** so we get the correct file name, then with strjoin we join the name with .cor
** the create the correct .cor file name and save it in fd_name which we return
*/

static	char	*get_name(char *argv)
{
	char	**name;
	char	*fd_name;

	name = ft_strsplit(argv, '.');
	fd_name = ft_strjoin(name[0], ".cor");
	free_split(name);
	return (fd_name);
}

/*
**	@brief: creates cor file
**
**	@param argv = is the string of the last argument
**	@param list = is structure with all needed data in it
**
**	create_cor_file is the main function for creating a .cor file
**	we get the correct .cor name by the return value of
**	get_name function and save it in fd_name.
*/

void			create_cor_file(char *argv, t_func_list *list)
{
	char	*fd_name;
	int		fd;

	fd_name = get_name(argv);
	fd = open(fd_name, O_CREAT | O_WRONLY | O_TRUNC, 0640);
	write_cor_file(fd, list);
	ft_printf("Wrote champion to %s\n", fd_name);
	free(fd_name);
}
