/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l1.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 05:25:21 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/02 12:57:16 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

/*
** read line for line in the file and process the line
*/

int		read_file(int fd, t_func_list *list)
{
	int ret;
	int process_ret;
	char *line;

	line = NULL;
	ret = 1;
	while (ret > 0)
	{
		process_ret = 0;
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (3);
		if (line != NULL && line[0] != '\0')
		{
			process_ret = process_line_into_list(list, line);
			if (process_ret != 0)
				return (process_ret);
		}
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}

/*
** check for the fd of the file
*/

int		transfer_into_struct(char *file_name, t_func_list *list)
{
	int			fd;
	int			ret;

	ret = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (2);
	ret = read_file(fd, list);
	if (ret != 0)
		return (ret);
	return (0);
}

/*
**	check if it ends on .s extention for assembly file
*/

int		check_correct_file(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	if (file_name[len - 1] == '.' && file_name[len] == 's')
		return (0);
	return (-1);
}

int		check_file(char *file_name, t_func_list *list)
{
	int ret;

	ret = 0;
	list->name = NULL;
	list->comment = NULL;
	list->info = NULL;
	if (check_correct_file(file_name) == -1)
		return (1);
	ret = transfer_into_struct(file_name, list);
	if (ret != 0)
		return (ret);
	return (0);
}
