/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 12:31:32 by igor          #+#    #+#                 */
/*   Updated: 2020/05/02 17:23:14 by igor          ########   odam.nl         */
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
	char	**name;
	char	*fd_name;
	int		i;

	i = 0;
	name = ft_strsplit(argv, '.');
	while (name[i] != NULL)
		i++;
	if (ft_strequ(name[i - 1], "cor") == 0)
	{
		ft_printf("Error, wrong file. Needs to be a .cor file\n");
		exit(-1);
	}
	fd_name = ft_strjoin(name[0], ".s");
	free_split(name);
	return (fd_name);
}
