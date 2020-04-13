/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_champ.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:37:30 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/13 12:42:24 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief writes size of executable champion commands into filediscriptor
**
** @param fd = filediscripter to write string in
** @param champ_size = size of the champion
**
** write_champ_size writes the size of only executable part of champion in filediscriptor
** it write the champ_size of a four byte size
*/

void	write_champ_size(int fd, int champ_size)
{
	if (champ_size > CHAMP_MAX_SIZE)
	/*need to place error message, need to give t_func_struct, but need to know where to find champ size in info*/
	{
		ft_putendl("champion is to big");
		exit(-1);
	}
	champ_size = rev_endian(champ_size);
	write(fd, &champ_size , 4);
}

/*
** @brief checks if there is an encoding byte and writes is in filediscripter
**
** @param fd = filediscripter to write string in
** @param encode = is data containing encode
*/
void	check_encode(int fd, char encode)
{
	if (encode != NULL)
		write(fd, &encode, 1);
}

/*
** @brief check_size checks the op_code and returns size 2 or 4 for T_DIR depending on op_code
**
** @param op_code = data of op_code
** @return size_t = size needed to T_DIR
*/
size_t	check_size(unsigned char op_code)
{
	if (op_code == 0x09 || op_code == 0x0a || op_code == 0x0b
		|| op_code == 0x0c || op_code == 0x0e || op_code == 0x0f)
		return(2);
	return(4);
}

/*
** @brief writes executable champion commands in byte_code into filediscriptor
**
** @param fd = filediscripter to write string in
** @param info = struct with needed data for writing champ
**
** write_champ writes all the labels and operations into byte_code into the filediscriptor
*/

void	write_champ(int fd, t_direction *info)
{
	t_direction	*probe;
	size_t		size;

	probe = info;
	while (probe->next != NULL)
	{
		check_encode(fd, probe->encode);
		size = check_size(info->op_code);
		write(fd, &probe->arg_num, size);
		write_null(fd, 0, 1);
		probe = probe->next;
	}
}
