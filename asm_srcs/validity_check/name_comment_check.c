/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   name_comment_check.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 14:30:59 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/05 15:42:12 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** name_check checks if the format and the size of name string are correct
*/

void	check_name(char *line)
{
	int		i;
	short	j;

	i = 0;
	j = 0;
	while (i < PROG_NAME_LENGTH)
	{
		if (i == 0 && ft_strrchr(&line[i],'"') != NULL)
			error_string(line);
		if ((i == 0 && ft_strrchr(&line[i],'"') != NULL) ||
		(ft_strrchr(&line[i],'"') != NULL && ft_strrchr(&line[i + 1], '\n') != NULL))
			j++;
		i++;
	}
	if (i > PROG_NAME_LENGTH)
		error_message(list, 7, 0);
	if (j != 2)
		error_message(list, 9, 0);
}

/*
** comment_check checks if the format and the size of comment string are correct
*/

void	check_comment(char *line)
{
	int		i;
	short	j;

	i = 0;
	j = 0;
	while (i < COMMENT_LENGTH)
	{
		if (i == 0 && ft_strrchr(&line[i],'"') != NULL)
			error_string(line);
		if ((i == 0 && ft_strrchr(&line[i],'"') != NULL) ||
		(ft_strrchr(&line[i],'"') != NULL && ft_strrchr(&line[i + 1], '\n') != NULL))
			j++;
		i++;
	}
	if (i > COMMENT_LENGTH)
		error_message(list, 8, 0);
	if (j != 2)
		error_message(list, 9, 0);
}
