/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_champ.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:37:30 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/20 16:42:17 by igvan-de      ########   odam.nl         */
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

/*
** @brief check_size checks the op_code and returns size 2 or 4 for T_DIR depending on op_code
**
** @param op_code = data of op_code
** @return size_t = size needed to T_DIR
*/

#include <stdio.h>
static size_t	check_size(unsigned char op_code)
{
	if (op_code == 0x09 || op_code == 0x0a || op_code == 0x0b
		|| op_code == 0x0c || op_code == 0x0e || op_code == 0x0f)
		return(2);
	return(4);
}

static	void	write_empty(int fd, size_t size)
{
	unsigned char byte;

	byte = 0;
	if (size == 4)
	{
		write(fd, &byte, 1);
		write(fd, &byte, 1);
	}
	write(fd, &byte, 1);
	write(fd, &byte, 1);
}

static void		write_dir(int fd, t_direction *info, int i)
{
	size_t size;
	unsigned char byte;

	size = check_size(info->op_code);
	if (info->arg_num[i] == 0)
	{
		write_empty(fd, size);
		return ;
	}
	if (size == 4)
	{
		byte = (unsigned char)(info->arg_num[i] >> 24);
		write(fd, &byte, 1);
		byte = (unsigned char)(info->arg_num[i] >> 16);
		write(fd, &byte, 1);
	}
	byte = (unsigned char)(info->arg_num[i] >> 8);
	write(fd, &byte, 1);
	byte = (unsigned char)info->arg_num[i];
	write(fd, &byte, 1);
}

static void	write_ind(int fd, t_direction *info, int i)
{
	unsigned char byte;

	byte = (unsigned char)(info->arg_num[i] >> 8);
	write(fd, &byte, 1);
	byte = (unsigned char)info->arg_num[i];
	write(fd, &byte, 1);
}

static void write_reg(int fd, t_direction *info, int i)
{
	char	arg;

	arg = (char)info->arg_num[i];
	write(fd, &arg, 1);
}

void	print_bits(unsigned char octet)
{
	int	i;

	i = 128;
	while (i)
	{
		(octet / i) ? write(1, "1", 1) : write(1, "0", 1);
		(octet / i) ? octet -= i : 0;
		i /= 2;
	}
	ft_putchar('\n');
}

static void check_value(int fd, unsigned char new ,t_direction *info, int i)
{
	if (new == DIR_CODE)
		write_dir(fd, info, i);
	else if (new == REG_CODE)
		write_reg(fd, info, i);
	else if (new == IND_CODE)
		write_ind(fd, info, i);
	else
	{
		printf("	error -> encode bitpair not recognized\n");
		print_bits(new);
		exit (0);
	}
}

int	has_encode(unsigned char op_code)
{
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
		return (0);
	return (1);
}

static void	write_encode(int fd, t_direction *info)
{
	static int left[3] = {0, 2, 4};
	unsigned char new;
	int		i;

	new = (unsigned char)info->encode;
	i = 0;
	if (has_encode(info->op_code) == 1)
		write(fd, &info->encode, 1);
	while (i < 3)
	{
		new = (unsigned char)info->encode;
		new <<= left[i];
		new >>= 6;
		if (new != 0)
			check_value(fd, new, info, i);
		i++;
	}
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

	probe = info;
	while (probe != NULL)
	{
		write(fd, &probe->op_code, 1);
		write_encode(fd, probe);
		probe = probe->next;
	}
}
