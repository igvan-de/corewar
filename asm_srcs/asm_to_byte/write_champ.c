/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_champ.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:37:30 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/13 14:09:03 by igvan-de      ########   odam.nl         */
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
static void	write_encode(int fd, char encode)
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

static size_t	check_size(unsigned char op_code)
{
	if (op_code == 0x09 || op_code == 0x0a || op_code == 0x0b
		|| op_code == 0x0c || op_code == 0x0e || op_code == 0x0f)
		return(2);
	return(4);
}

/*
** @brief write_dir looks via check_size the size of T_DIR and write bytes of size in fd
**
** @param fd = filediscripter to write string in
** @param info = contains all needed data, op_code and arg_num
*/

static void		write_dir(int fd, t_direction *info)
{
	size_t size;

	size = check_size(info->op_code);
	write(fd, &info->arg_num, size);
}

/*
** @brief
**
** @param fd = filediscripter to write string in
** @param arg_num = argument to write in filediscriptor
*/

static void	write_ind(int fd, int arg_num)
{
	write(fd, (short)&arg_num, 2);
}

/*
** @brief write_reg writes the size of T_REG in filediscriptor
**
** @param fd = filediscripter to write string in
** @param arg_num = argument to write in filediscriptor
*/
static void write_reg(int fd, int arg_num)
{
	if (arg_num != 0)
		write(fd, (unsigned char)&arg_num, 1);
	else
		write(fd, 0, 1);
}

/*
** @brief writes executable champion commands in byte_code into filediscriptor
**
** @param fd = filediscripter to write string in
** @param info = struct with needed data for writing champ
**
*/

void	write_champ(int fd, t_direction *info)
{
	t_direction	*probe;
	size_t		size;

	probe = info;
	while (probe->next != NULL)
	{
		write_encode(fd, probe->encode);
		if (probe->arg_num == T_DIR)
			write_dir(fd, probe->arg_num);
		if (probe->arg_num == T_IND)
			write_ind(fd, probe->arg_num);
		if (probe->arg_num == T_REG)
			write_reg(fd, probe->arg_num);
		write_null(fd, 0, 1);
		probe = probe->next;
	}
}
