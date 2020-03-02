/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validity_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 18:41:25 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/02 14:36:01 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** check_name iterates through line, if '"' is found it will count
** how the size of name_program and if second '"' is found
*/

static void check_name(char *line)
{
	int	i;
	int	j;

	i= 0;
	j = 0;
	while (line[i] != '\n')
	{
		if (ft_strequ(line[i], '"') != false)
		{
			j++; // to save how many " there are found
			i--; //" char does not count in size of comment
		}
		if (i > PROG_NAME_LENGTH)
			return (16);
		i++;
	}
	if (j == 0 || j == 1)
		return (17);
}

/*
** check_comment iterates through line, if '"' is found it will count
** how the size of comment and if second '"' is found
*/

static void	check_comment(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	// maybe check first for " symbols?!, then start while loop
	while (line[i] != '\n')
	{
		if (ft_strequ(line[i], '"') != false)
		{
			j++; // to save how many " there are found
			i--; //" char does not count in size of comment
		}
		if (i > COMMENT_LENGTH)
			return (16);
		i++;
	}
	if (j == 0 || j == 1)
		return (17);
}

int			validity_check_line(char **line)
{
	if (ft_strequ(line[NAME], NAME_CMD_STRING) == 0)
		check_name(line[STRING]);
	if (ft_strequ(line[COMMENT], COMMENT_CMD_STRING) == 0)
		check_comment(line[STRING]);
	if (ft_strequ(line, LABEL_CHARS) == 0)
		return (15); //need to check if this is an ok error_output
	return (0);
}
