/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_rem_cn.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/03 20:14:37 by mark          #+#    #+#                 */
/*   Updated: 2020/05/03 22:49:13 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	add_newline(t_func_list *list, char **target)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_strjoin(*target, "\n");
	if (!tmp)
		error_message(list, 0, 0, 0);
	free(*target);
	*target = ft_strdup(tmp);
	if (!*target)
		error_message(list, 0, 0, 0);
	free(tmp);
}

static void	no_quotes(t_func_list *list, char **target, int ret)
{
	char	*tmp2;

	tmp2 = NULL;
	if (ret == 0)
		error_message(list, 0, 0, 0);
	if (list->line == NULL)
		return (add_newline(list, target));
	tmp2 = ft_strjoin(*target, list->line);
	if (!tmp2)
		error_message(list, 0, 0, 0);
	free(*target);
	*target = ft_strdup(tmp2);
	free(tmp2);
	add_newline(list, target);
}

static void	found_quotes(t_func_list *list, int start, char **target)
{
	char	*sub;
	char	*tmp;

	sub = NULL;
	sub = ft_strsub(list->line, start, list->line_char - start);
	if (!sub)
		error_message(list, 0, 0, 0);
	tmp = ft_strjoin(*target, sub);
	if (!tmp)
		error_message(list, 0, 0, 0);
	free(*target);
	*target = NULL;
	ft_memdel((void **)&sub);
	*target = ft_strdup(tmp);
	free(tmp);
	if ((int)ft_strlen(*target) > list->cn_size)
		error_message(list, 0, 0, 0);
	list->cn_size = 0;
}

void		get_rem_cn(t_func_list *list, int ret)
{
	int		start;
	char	**target;

	target = NULL;
	if (list->cn_size == PROG_NAME_LENGTH)
		target = &list->name;
	else
		target = &list->comment;
	start = list->line_char;
	while (list->line[list->line_char] && list->line[list->line_char] != '\"')
		list->line_char++;
	if (list->line[list->line_char] == '\"')
		found_quotes(list, start, target);
	else
		no_quotes(list, target, ret);
}
