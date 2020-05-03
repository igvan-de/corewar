/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_name_comment.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 10:58:40 by mlokhors      #+#    #+#                 */
/*   Updated: 2020/05/03 22:49:36 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** This function search for the end of the string. so the other " character
** if it doesnt find it will give an error
*/

static void	found_str(t_func_list *list, char *line, char **target, int len)
{
	int		start;
	char	*tmp;

	tmp = NULL;
	start = list->line_char;
	while (line[list->line_char] && line[list->line_char] != '\"')
		list->line_char++;
	if (list->line_char - start < len)
	{
		*target = ft_strsub(line, start,
		list->line_char - start);
		list->line_char++;
		if (*target == NULL)
			error_message(list, 32, 3, 3);
	}
	else
		error_message(list, 33, 4, 3);
	if (line[list->line_char - 1] != '\"')
	{
		list->cn_size = len;
		tmp = ft_strjoin(*target, "\n");
		free(*target);
		*target = tmp;
	}
}

/*
** it will search for the start character of a string
** if there is a character that is not a " it will exit it
*/

static void	search_for_str(t_func_list *list, char *line,
		char **target, int len)
{
	skip_space(list);
	if (line[list->line_char] && line[list->line_char] != '\"')
	{
		if (line[list->line_char + 1] != '\0')
			list->line_char++;
		error_message(list, 39, 0, 3);
	}
	list->line_char++;
	found_str(list, line, target, len);
	check_end_line(list);
}

/*
** compares it with name or comment.
** if that is the same it will adds the length. so it keeps going
** else it its not a valid input since we already checked for the '.'
*/

void		get_name_comment(t_func_list *list)
{
	char *line;

	line = list->line;
	if (ft_strncmp(line + list->line_char, "name", 4) == 0)
	{
		if (list->name != NULL)
			error_message(list, 34, 5, 3);
		list->line_char += 4;
		search_for_str(list, line, &(list->name), PROG_NAME_LENGTH);
	}
	else if (ft_strncmp(line + list->line_char, "comment", 7) == 0)
	{
		if (list->comment != NULL)
			error_message(list, 35, 6, 3);
		list->line_char += 7;
		search_for_str(list, line, &(list->comment), COMMENT_LENGTH);
	}
	else
	{
		list->line_char++;
		error_message(list, 30, 0, 3);
	}
}
