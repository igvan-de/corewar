/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validity_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 18:41:25 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/02 16:44:58 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** check_label check if label only has chars same as LABEL_CHARS
** and it ends with a LABEL_CHAR as it needs to have
*/

static int check_label(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (ft_strequ(line[i], LABEL_CHARS) == false && ft_strequ(line[i], LABEL_CHAR) == false)
			return (15); // need to determine error value
		i++;
	}
	return (true);
}

/*
** check_name iterates through line, if '"' is found it will count
** how the size of name_program and if second '"' is found
*/

static int check_name(char *line)
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
			return (16); // need to determine error value
		i++;
	}
	if (j == 0 || j == 1)
		return (17); // need to determine error value
	return (true);
}

/*
** check_comment iterates through line, if '"' is found it will count
** how the size of comment and if second '"' is found
*/

static int	check_comment(char *line)
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
			return (16); //need to determine error value
		i++;
	}
	if (j == 0 || j == 1)
		return (17); // need to determine error value
	return (true);
}

int			validity_check_line(char **line)
{
	int ret;

	ret = 0;
	if (ft_strequ(line[NAME], NAME_CMD_STRING) == 0)
	{
		ret = check_name(line[STRING]);
		if (ret != true)
			return (ret);
	}
	if (ft_strequ(line[COMMENT], COMMENT_CMD_STRING) == 0)
	{
		ret = check_comment(line[STRING]);
		if (ret != true)
			return (ret);
	}
	if (ft_strequ(line, LABEL_CHARS) == 0)
	{
		ret = check_label(line[LABEl]);
		if (ret != true)
			return (ret);
	}
	return (true);
}
