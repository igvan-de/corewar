/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_n_process.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 05:25:21 by mlokhors      #+#    #+#                 */
/*   Updated: 2020/04/22 19:53:34 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

/*
** read the file line for line.
**	if there is only a label it will not make a new node.
** it will go to the next line but its still the same node.
** after it ready it transforms the labels which came in als arguments
** to the index number
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
		if (check_empty_line(list) == false)
			process_line_into_list(list);
		ft_memdel((void **)&list->line);
		list->line_number++;
	}
	close(fd);
	transfrom_arg_label(list);
}

/*
** check for the fd of the file and checks if its valid
*/

static void		transfer_into_struct(char *file_name, t_func_list *list)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_message(list, 11, 1, 1);
	read_file(list, fd);
}

/*
**	check if it ends on .s extention for assembly file
*/

static bool		check_correct_file(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	if (file_name[len - 2] == '.' && file_name[len - 1] == 's')
		return (true);
	return (false);
}

void			check_n_process(char *file_name, t_func_list *list)
{
	if (check_correct_file(file_name) == false)
		error_message(list, 10, 0, 1);
	transfer_into_struct(file_name, list);
}
