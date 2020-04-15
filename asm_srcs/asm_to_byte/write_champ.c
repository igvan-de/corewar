/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_champ.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:37:30 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/15 07:31:13 by mark          ########   odam.nl         */
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
	{
		/*need to place error message, need to give t_func_struct, but need to know where to find champ size in info*/
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

static void	write_encode(int fd, t_direction *info)
{
	if (info->op_code != 0x01 || info->op_code != 0x09 || info->op_code != 0x0c
	|| info->op_code != 0x0f)
		write(fd, &info->encode, 1);
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

// zo werkt t_dir niet. het is of een short(16 bits) of een int container(32) bits

static void		write_dir(int fd, int arg, char opcode)
{
	size_t size;

	size = check_size(opcode);
	write(fd, &arg, size);
}

/*
** @brief
**
** @param fd = filediscripter to write string in
** @param arg_num = argument to write in filediscriptor
*/

static void	write_ind(int fd, int arg_num)
{
	short	arg;

	arg = (short)arg_num;
	write(fd, &arg, 2);
}

/*
** @brief write_reg writes the size of T_REG in filediscriptor
**
** @param fd = filediscripter to write string in
** @param arg_num = argument to write in filediscriptor
*/

// waarom deze cast?
// je weet als je van encode afleest dan maakt het toch niks meer uit?

static void write_reg(int fd, int arg_num)
{
	char	arg;

	arg = (char)arg_num;
	if (arg_num != 0)
		write(fd, &arg, 1);
	else
		write(fd, 0, 1);
}

// maken van deze ipv 3 4 en zet de 0 waarde op NULL

static void	func_pointer_arr(int value)
{
	const func_pointer[3] = {write_dir, write_ind, write_reg};
	func_pointer[value];
}

static void	write_args(int fd, t_direction *info)
{
	func_pointer_arr();
}

/*
** @brief writes executable champion commands in byte_code into filediscriptor
**
** @param fd = filediscripter to write string in
** @param info = struct with needed data for writing champ
**
*/

// waarom een adress van probe->op_code?
// je hoeft deze niet mmer veranderen.
// put_nbr niet beter? 
// write accepteerd het zo niet volgens mij

void	write_champ(int fd, t_direction *info)
{
	t_direction	*probe;

	probe = info;
	while (probe != NULL)
	{
		write(fd, &probe->op_code, 1);
		write_encode(fd, probe->encode);
		write_args(fd, info);
		probe = probe->next;
	}
}
