/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_cor_file.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 17:41:05 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/09 20:25:46 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief magic header object
**
** @param fd = is filediscriptor to place magic header in
** @param list = is structure with all needed data in it
**
** magic_header we always start with placing the magic_header in .cor file
** and then continueing to convert name, comment executable code into .cor file
*/

static void	write_magic_header(int fd)
{
	int	magic;

	magic = rev_endian(COREWAR_EXEC_MAGIC);
	write(fd, &magic, 4);
}

/*
** @brief
**
** @param fd
** @param list
**
** convert_name, convert de .name van de champion into byte code for the .cor file
** it checks if the size is correct
*/

static void	write_name(int fd, t_func_list *list)
{
	int		index;
	int		ascii_value;
	char	*name;

	index = 0;
	name = list->name;
	while (name[index])
	{
		ft_printf("name = %c\n", name[index]);
		ascii_value = name[index];
		printf("ascii = %i\n", ascii_value);
		index++;
	}
	ascii_value = rev_endian(ascii_value);
	write(fd, &ascii_value, index);
}

/*
** convert_name, convert de .comment van de champion into byte code for the .cor file
** it checks if the size is correct
*/

// static void	write_comment(t_func_list *list)
// {

// }

void	write_cor_file(int fd, t_func_list *list)
{
	write_magic_header(fd);
	write_name(fd, list);
}
