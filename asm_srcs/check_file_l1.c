/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l1.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 05:25:21 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/06 17:34:46 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

/*
** read_file read line for line the given champin file
** and check if the format is correct in the function validity_check
*/

void	pre_process_line(t_func_list *list, char *line, int ret)
{
	if (line != NULL && line[0] != '\0')
		process_line_into_list(list, line);
	free(line);
	line = NULL;
}

/*
** read the file line for line
*/

void	read_file(int fd, t_func_list *list)
{
	int		ret;
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		list->line_char = -1;
		list->line_number++;
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			close(fd);
			error_messege(list, 4, 2);
		}
		pre_process_line(list, line, ret);
	}
	close(fd);
}

/*
** check for the fd of the file
*/

void	transfer_into_struct(char *file_name, t_func_list *list)
{
	int			fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (error_messege(list, 3, 2));
	read_file(fd, list);
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

void	check_file(char *file_name, t_func_list *list)
{
	if (check_correct_file(file_name) == -1);
		return (error_messege(list, 2, 2));
	transfer_into_struct(file_name, list);
}
