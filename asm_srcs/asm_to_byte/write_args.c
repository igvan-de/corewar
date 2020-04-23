/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:37:30 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/20 16:42:17 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

	size = get_tdir_size(info->op_code);
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

void write_args(int fd, unsigned char new ,t_direction *info, int i)
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
