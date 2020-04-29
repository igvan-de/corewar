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

/*
**	@brief:	write zeroed bytes into .cor file
**
**	@param fd	:	.cor file descriptor
**	@param info	:	operation data
**	@param	i	:	argument index
**
**	write_reg receives the operation data and
**	writes size zeroed bytes into the .cor file.
**	size can either be four or two bytes.
*/

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

/*
**	@brief:	write direct value into .cor file
**
**	@param fd	:	.cor file descriptor
**	@param info	:	operation data
**	@param	i	:	argument index
**
**	write_reg receives the operation data and writes a
**	direct value into the .cor file. Written value can
**	either be four or two bytes, depending on the performing
**	operation.
*/

static	void	write_dir(int fd, t_direction *info, int i)
{
	size_t			size;
	unsigned char	byte;

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

/*
**	@brief:	write indirect value into .cor file
**
**	@param fd	:	.cor file descriptor
**	@param info	:	operation data
**	@param	i	:	argument index
**
**	write_ind receives the operation data and writes an
**	indirect value into the .cor file.
*/

static	void	write_ind(int fd, t_direction *info, int i)
{
	unsigned char byte;

	byte = (unsigned char)(info->arg_num[i] >> 8);
	write(fd, &byte, 1);
	byte = (unsigned char)info->arg_num[i];
	write(fd, &byte, 1);
}

/*
**	@brief:	write register number into .cor file
**
**	@param fd	:	.cor file descriptor
**	@param info	:	operation data
**	@param	i	:	argument index
**
**	write_reg receives the operation data and writes a
**	register number into the .cor file.
*/

static	void	write_reg(int fd, t_direction *info, int i)
{
	char	arg;

	arg = (char)info->arg_num[i];
	write(fd, &arg, 1);
}

/*
**	@brief:	write argument values into .cor file
**
**	@param fd	:	.cor file descriptor
**	@param new	:	encode byte bitpair
**	@param info	:	operation data
**	@param	i	:	argument index
**
**	write_args receives the operation data and writes the argument value
**	into the .cor file. works for each argument type.
*/

void			write_args(int fd, unsigned char new, t_direction *info, int i)
{
	if (new == DIR_CODE)
		write_dir(fd, info, i);
	else if (new == REG_CODE)
		write_reg(fd, info, i);
	else if (new == IND_CODE)
		write_ind(fd, info, i);
}
