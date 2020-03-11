/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l2_1_get_name_com.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 10:58:40 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/11 15:14:00 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** This function search for the end of the string. so the other " character
** if it doesnt find it will give an error
*/

void	found_str(t_func_list *list, char *line, char **target, int len)
{
	int start;

	start = list->line_char;
	while (line[list->line_char] && line[list->line_char] != "\"")
		list->line_char++;
	if (list->line_char == ft_strlen(line))
		error_message(list, 102, 5);
	if (line[list->line_char] == "\"")
	{
		if (list->line_char - start < len)
		{
			*target = ft_strsub(line, start,
			list->line_char - start);
			if (*target == NULL)
				error_message(list, 5, 2);
		}
		else
			error_message(list, 6, 4);
	}
}

/*
** it will search for the start character of a string
** if there is a character that is not a " it will exit it
*/

void	search_for_str(t_func_list *list, char *line, char **target, int len)
{
	int	iter;

	iter = 0;
	while (line[list->line_char] && ft_isspace(line[list->line_char]) == 1)
		list->line_char++;
	if (line[list->line_char] && line[list->line_char] != "\"")
	{
		if (line[list->line_char + 1] != '\0')
			list->line_char++;
		error_messege(list, 102, 5);
	}
	list->line_char++;
	found_str(list, line, target, len);
}

/*
** cmp it with name or comment.
** if that is equal it will adds the length. so it keeps going
*/

void	get_name_or_comment(t_func_list *list, char *line)
{
	if (ft_strncmp(line + list->line_char, "name", 4) == 0)
	{
		list->line_char += 5;
		search_str(list, line, &(list->name), PROG_NAME_LENGTH);
	}
	else if (ft_strncmp(line + list->line_char, "comment", 7) == 0)
	{
		list->line_char += 8;
		insert_str(list, line, &(list->comment), COMMENT_LENGTH);
	}
	else
	{
		list->line_char++;
		error_messege(list, 102, 5);
	}
}
