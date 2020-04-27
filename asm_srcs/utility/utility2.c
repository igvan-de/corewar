/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 17:47:08 by mark          #+#    #+#                 */
/*   Updated: 2020/04/28 00:56:08 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_between(t_func_list *list, int err, int err_p, int err_f)
{
	if (list->line[list->line_char] != SEPARATOR_CHAR &&
		list->line[list->line_char] != '\0' &&
		ft_isspace(list->line[list->line_char]) == 0 &&
		list->line[list->line_char] != COMMENT_CHAR)
		error_message(list, err, err_p, err_f);
}

void	skip_space(t_func_list *list)
{
	while (list->line[list->line_char] &&
		ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
}
