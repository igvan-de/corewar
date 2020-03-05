/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l1.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 05:25:21 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/05 13:04:55 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

/*
** read_file read line for line the given champin file
** and check if the format is correct in the function validity_check
*/

static void		read_file(int fd, t_func_list *list)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		validity_check(line, list);
		free(line);
	}
	close(fd);
}

/*
** check for the fd of the file
*/

static void		transfer_into_struct(char *file_name, t_func_list *list)
{
	int			fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_message(list, 5, 0);
	read_file(fd, list);
}

/*
**	check if it ends on .s extention for assembly file
*/

static bool		check_correct_file(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	if (file_name[len - 1] == '.' && file_name[len] == 's')
		return (true);
	return (false);
}

/*
** check_file is the main function which will move to other functions
** to check is the given file is correct formated and if tits the right .s file
*/

void		check_file(char *file_name, t_func_list *list)
{
	if (check_correct_file(file_name) == false)
		error_message(&list, 4, 0);
	transfer_into_struct(file_name, list);
}
