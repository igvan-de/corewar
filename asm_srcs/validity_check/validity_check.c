/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validity_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 18:41:25 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/05 14:29:36 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** check_split_line, checks the the value of split_line, if its a name, comment or label
*/

static void	check_split_line(char **split_line)
{
	if (ft_strequ(split_line[NAME], NAME_CMD_STRING) == true)
	{
		check_name(split_line[STRING]);
		return ;
	}
	if (ft_strequ(split_line[COMMENT], COMMENT_CMD_STRING) == true)
	{
		check_comment(split_line[STRING]);
		return ;
	}
	/*check label!*/
}


/*
** validity_check, checks if line are correctly formatted by going through multiple
** different functions who check in more detail if format is correctly and size of string
*/

void		validity_check(char *line, t_func_list *list)
{
	char	**split_line;

	if (line == NULL)
		error_message(list, 6, 0);
	split_line = ft_strsplit(line, ' ');
	check_split_line(split_line);
}
