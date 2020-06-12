/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 09:02:17 by mark          #+#    #+#                 */
/*   Updated: 2020/06/11 17:02:26 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief checks if the last line is empty or is a commnet
**
** @param 	list = the container where we store all our information
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
**
** @return	it sets the return to 3 if the last line is empty
**			this is needed so it can compile with an empty line
*/

static int		check_empty_ret(t_func_list *list, int ret)
{
	if (ret != 1)
		return (ret);
	skip_space(list);
	if ((list->line[list->line_char] == '#' ||
	list->line[list->line_char] == '\0'))
		return (ret + 2);
	return (ret);
}

/*
** @brief checks for the remains after all being extracted from line
**
** @param 	list = the container where we store all our information
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
*/

static bool		check_empty_line(t_func_list *list)
{
	if (list->line == NULL)
		return (true);
	while (list->line != NULL && list->line[list->line_char] &&
	ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
	if (list->line != NULL && list->line[list->line_char] != '\0' &&
		list->line[list->line_char] != COMMENT_CHAR)
		return (false);
	return (true);
}

/*
** @brief	pre processing line.
**
** @param 	list = the container where we store all our information
** @param	list->cn_size = is needed to determine if its a comment or a name
** @param 	ret = return value of gnl to check if line ended with newline
** @param 	old_ret = return previous value of gnl to
**			check if line ended with newline
**
** first condition is to check if a name or comment are on multiple lines
** second condition is to check if the end of file ends on a new line
** third condition further processing the line
*/

static void		pre_process(t_func_list *list, int ret, int old_ret)
{
	if (list->cn_size != 0 && ret == 0)
		error_message(list, 142, 2, 14);
	if (list->cn_size != 0)
		get_rem_cn(list, ret);
	else if (old_ret == 1 && ret == 0)
		error_message(list, 141, 1, 14);
	else if (check_empty_line(list) == false)
		process_line(list);
}

/*
** @brief	reads from the file.
**
** @param 	list = the container where we store all our information
** @param 	fd = file descriptor of the file
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
** @param	list->line_number = is the line number readed from file.
** @param 	ret = return value of gnl to check if line ended with newline
** @param 	old_ret = return previous value of gnl to
**			check if line ended with newline
**
** its reads line by line from the file. after each read it will process
** the line.
*/

void			read_file(t_func_list *list, int fd)
{
	int		ret;
	int		old_ret;

	old_ret = 0;
	ret = 1;
	list->line_number++;
	while (ret > 0)
	{
		list->line_char = 0;
		ret = get_next_line(fd, &list->line);
		if (ret == -1)
		{
			close(fd);
			error_message(list, 140, 0, 14);
		}
		ret = check_empty_ret(list, ret);
		pre_process(list, ret, old_ret);
		ft_memdel((void **)&list->line);
		old_ret = ret;
		list->line_number++;
	}
	close(fd);
	transform_label(list);
}
