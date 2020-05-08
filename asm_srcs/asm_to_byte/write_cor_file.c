/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_cor_file.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 17:41:05 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/18 11:01:22 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief writes magic header into filediscriptor
**
** @param fd = is filediscriptor to place magic header in
** @param list = is structure with all needed data in it
**
** magic_header we always start with placing the magic_header in .cor file
** and then continueing to convert name, comment executable code into .cor file
*/

static	void	write_magic_header(int fd)
{
	int	magic;

	magic = rev_endian(COREWAR_EXEC_MAGIC);
	write(fd, &magic, 4);
}

/*
** @brief writes null into filediscriptor
**
** @param fd = filediscripter to wright nulls in
** @param index = the size of filediscriptor already filled
** @param limit = the max size of how many null still need to be filled
**
** this function write null until the limit size starting from index
*/

static	void	write_null(int fd, int index, int limit)
{
	while (index < limit)
	{
		write(fd, "\0", 1);
		index++;
	}
}

/*
** @brief writes string into filediscriptor
**
** @param fd = filediscripter to write string in
** @param string = is string wanted to be written in filediscriptor
** @param limit = max size of string allowed
**
** convert_name, convert de .name van de champion into
** byte code for the .cor file
** it checks if the size is correct
*/

static	void	write_string(int fd, char *string, int limit)
{
	int		index;
	char	ascii_value;

	index = 0;
	if (string)
	{
		while (string[index] != '\0')
		{
			ascii_value = string[index];
			write(fd, &ascii_value, 1);
			index++;
		}
	}
	write_null(fd, index, limit);
}

/*
** @brief writes all needed data into filediscriptor
**
** @param fd = filediscripter to write string in
** @param list = struct containing all needed data
**
** write_cor_file writes all needed data into filediscriptor (.cor)
** it always starts with magic_header, otherwise its a invalid file for the VM
** write_string writes the name or comment into the filediscriptor,
** depended on which string you give the function and it also writes
** 0 at the end until max_size for name or comment
** write_null writes 0 on four bytes, needed for a valid .cor file
** write_champ_size writes the size of executable code of champion
** into four bytes in filediscriptor
** write_champ writes all labels and operations into filediscriptor,
** what will be the executable code of the .cor file
*/

void			write_cor_file(int fd, t_func_list *list)
{
	write_magic_header(fd);
	write_string(fd, list->name, PROG_NAME_LENGTH);
	write_null(fd, 0, 4);
	write_champ_size(fd, list->total_bytes);
	write_string(fd, list->comment, COMMENT_LENGTH);
	write_null(fd, 0, 4);
	write_champ(fd, list->info);
}
