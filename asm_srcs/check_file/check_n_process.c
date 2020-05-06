/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_n_process.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 05:25:21 by mlokhors      #+#    #+#                 */
/*   Updated: 2020/05/06 09:05:00 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief open the file and check if its valid
**
** @param file_name = the file
** @param list = the container where we store all our information
*/

static void		transfer_into_struct(char *file_name, t_func_list *list)
{
	int			fd;
	int			bytes;
	t_header	test;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_message(list, 11, 1, 1);
	bytes = read(fd, &test, sizeof(t_header));
	if (bytes < 1)
		error_message(list, 12, 2, 1);
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
