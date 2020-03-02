/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l2_process_line.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 05:22:10 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/02 16:46:06 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_strnnchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

int		insert_name_comment(t_func_list *list, char *line, int sort)
{
	char	*start_line;
	int		start;
	int		end;

	end = 0;
	start_line = line;
	start = ft_strnnchr(line, '\"');
	start_line += start + 1;
	end = ft_strnnchr(start_line, '\"');
	if (sort == 0)
	{
		list->name = ft_strsub(line, start, end - start - 1);
		if (list->name == NULL)
			return (4);
	}
	else
	{
		list->comment = ft_strsub(line, start, end - start - 1);
		if (list->comment == NULL)
			return (5);
	}
	return (0);
}

/*
** this will decide if its name, comment, or an instruction
*/

int		process_line(t_func_list *list, char *line, char **line_split)
{
	// if (validity_check_line(line_split) != true)
	// 	return (check_file(line, i);
	if (ft_strcmp(line_split[NAME], NAME_CMD_STRING) && validity_check_line(line_split) == true)
		return (insert_name_comment(list, line, 0));
	else if (ft_strcmp(line_split[COMMENT], COMMENT_CMD_STRING) && validity_check_line(line_split) == true)
		return (insert_name_comment(list, line, 1));
	else
	{
		if (list->name != NULL)
		{
			if (line_split[0][ft_strlen(line_split[0])] == ':')
				return(insert_instruction(list, line_split, 1));
			else
				return(insert_instruction(list, line_split, 0));
		}
		else
			return (8);
	}
	return (9);
}

void	free_split(char **split)
{
	char *line;

	line = NULL;
	while (**split)
	{
		line = *split;
		*split += 1;
		free(line);
	}
}

/*
**	because it can contain as many spaces we split it up in a double array
**	ft_strplit need to be worked on to split it on a , aswell but only one
**	,, is error
*/

int		process_line_into_list(t_func_list *list, char *line)
{
	char	**split_line;
	int		ret;

	ret = 0;
	split_line = ft_strsplit(line, ' ');
	if (split_line == NULL)
		return (6);
	ret = process_line(list, line, split_line);
	free_split(split_line);
	if (ret != 0)
		return (ret);
	return (0);
}
