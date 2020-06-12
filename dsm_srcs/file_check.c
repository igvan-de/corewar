/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 12:31:32 by igor          #+#    #+#                 */
/*   Updated: 2020/06/11 11:34:48 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

/*
** @brief file_check first splits the given arguments on '.' character,
** afterwards it checks if the given file is an .cor file.
**
**
** @param argv = the complete argument which contains the name of file
** @return char* = the .s filename
*/

char	*file_check(char *argv)
{
	char	*name;
	char	*check;
	char	*fd_name;

	name = ft_strsub(argv, 0, ft_strlen(argv) - 4);
	check = ft_strsub(argv, ft_strlen(name), ft_strlen(argv));
	if (ft_strequ(check, ".cor") == 0)
	{
		ft_printf("Error, wrong file. Needs to be a .cor file\n");
		exit(1);
	}
	fd_name = ft_strjoin(name, ".s");
	if (!fd_name)
	{
		ft_printf("ft_strjoin in file_check failed\n");
		exit(1);
	}
	ft_printf(".s file is placed in: %s\n", fd_name);
	free(name);
	free(check);
	return (fd_name);
}
