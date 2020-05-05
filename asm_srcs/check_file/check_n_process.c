/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_n_process.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 05:25:21 by mlokhors      #+#    #+#                 */
/*   Updated: 2020/05/04 01:08:44 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

/*
** @brief checks for the remains after all being extracted from line
**
** @param 	list = the container where we store all our information
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
*/

static bool		check_empty_line(t_func_list *list)
{
	while (list->line != NULL && list->line[list->line_char] &&
	ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
	if (list->line != NULL && list->line[list->line_char] != '\0' &&
		list->line[list->line_char] != COMMENT_CHAR)
		return (false);
	return (true);
}

/*
** @brief	reads from the file.
**
** @param 	list = the container where we store all our information
** @param 	fd = file descriptor of the file
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
** @param	list->line_number = is the line number readed from file.
** @param	list->cn_size = is needed to determine if its a comment or a name
**
** its reads line by line from the file. after each read it will process
** the line.
*/

static void		read_file(t_func_list *list, int fd)
{
	int		ret;

	ret = 1;
	list->line_number++;
	while (ret > 0)
	{
		list->line_char = 0;
		ret = get_next_line(fd, &list->line);
		if (ret == -1)
		{
			close(fd);
			error_message(list, 12, 2, 1);
		}
		if (list->cn_size != 0)
			get_rem_cn(list, ret);
		else if (check_empty_line(list) == false)
			process_line(list);
		ft_memdel((void **)&list->line);
		list->line_number++;
	}
	close(fd);
	transform_label(list);
}

/*
** @brief open the file and check if its valid
**
** @param file_name = the file
** @param list = the container where we store all our information
*/

static void		transfer_into_struct(char *file_name, t_func_list *list)
{
	int fd;
	int bytes;
	t_header test;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_message(list, 11, 1, 1);
	bytes = read(fd, &test, sizeof(t_header));
	if (bytes < 1)
		error_message(list, 11, 1, 1);
	else
	{
		close(fd);
		fd = open(file_name, O_RDONLY);
	}
	read_file(list, fd);
}

/*
** @brief just to pre-check for the  correct file file
**
** @param file_name = the file
**
** check if it ends on .s extention for assembly file
*/

static bool		check_correct_file(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	if (file_name[len - 2] == '.' && file_name[len - 1] == 's')
		return (true);
	return (false);
}

/*
** @brief just to pre-check for the  correct file file
**
** @param file_name = the file
** @param list the container where we store all our information
*/

void			check_n_process(char *file_name, t_func_list *list)
{
	if (check_correct_file(file_name) == false)
		error_message(list, 10, 0, 1);
	transfer_into_struct(file_name, list);
}
