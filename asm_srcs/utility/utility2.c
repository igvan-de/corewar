/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 17:47:08 by mark          #+#    #+#                 */
/*   Updated: 2020/05/06 14:00:25 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief 	checking between operation arguments on invalid characters
**
** @param 	list = the container where we store all our information
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
*/

void	check_between(t_func_list *list, int err, int err_p, int err_f)
{
	if (list->line[list->line_char] != SEPARATOR_CHAR &&
		list->line[list->line_char] != '\0' &&
		ft_isspace(list->line[list->line_char]) == 0 &&
		list->line[list->line_char] != COMMENT_CHAR)
		error_message(list, err, err_p, err_f);
}

/*
** @brief skiping all spaces
**
** @param 	list = the container where we store all our information
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
*/

void	skip_space(t_func_list *list)
{
	if (list->line[list->line_char] == '\0')
		return ;
	while (list->line[list->line_char] &&
		ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
}
