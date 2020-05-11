/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_rem_cn.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/03 20:14:37 by mark          #+#    #+#                 */
/*   Updated: 2020/05/06 15:40:01 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief	just add a new line to name or comment
**
** @param	list = the container where we store all our information
** @param	target = memory adress of name or comment
*/

static void	add_newline(t_func_list *list, char **target)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_strjoin(*target, "\n");
	if (!tmp)
		error_message(list, 130, 0, 0);
	free(*target);
	*target = ft_strdup(tmp);
	if (!*target)
		error_message(list, 131, 0, 0);
	free(tmp);
}

/*
** @brief	it has found the end of a comment or name
**
** @param	list = the container where we store all our information
** @param	list->line = it readed line by line from the file and assign to line
** @param	ret = is needed so we can check if the file is finished
**			if the file is done with reading ant it comes in this function
**			then it means there is no second '"' to close off comment or name
** @param	target = memory adress of name or comment
**
** this function will at the last part of a name or a comment
*/

static void	no_quotes(t_func_list *list, char **target, int ret)
{
	char	*tmp2;

	tmp2 = NULL;
	if (ret == 0)
		error_message(list, 132, 0, 13);
	if (list->line == NULL)
		return (add_newline(list, target));
	tmp2 = ft_strjoin(*target, list->line);
	if (!tmp2)
		error_message(list, 133, 0, 13);
	free(*target);
	*target = ft_strdup(tmp2);
	free(tmp2);
	add_newline(list, target);
	if ((int)ft_strlen(*target) > list->cn_size)
		error_message(list, 137, 1, 13);
}

/*
** @brief	it has found the end of a comment or name
**
** @param	list = the container where we store all our information
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
** @param	start = is the beginning of the last part of the name or comment
**			together with line->char current position we can make a substring
** @param	target = memory adress of name or comment
**
** this function will at the last part of a name or a comment
*/

static void	found_quotes(t_func_list *list, int start, char **target)
{
	char	*sub;
	char	*tmp;

	sub = NULL;
	sub = ft_strsub(list->line, start, list->line_char - start);
	if (!sub)
		error_message(list, 134, 0, 13);
	tmp = ft_strjoin(*target, sub);
	if (!tmp)
		error_message(list, 135, 0, 13);
	free(*target);
	*target = NULL;
	ft_memdel((void **)&sub);
	*target = ft_strdup(tmp);
	free(tmp);
	if ((int)ft_strlen(*target) > list->cn_size)
		error_message(list, 136, 1, 13);
	list->cn_size = 0;
	if (list->line[list->line_char] == '\0')
		return ;
	list->line_char++;
	check_end_line(list);
}

/*
** @brief	checks where the end of name of comment is
**
** @param	list = the container where we store all our information
** @param	ret = checks if the file still keeps reading or is finished
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
** @param	list->cn_size = is needed to determine if its a comment or a name
*/

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
