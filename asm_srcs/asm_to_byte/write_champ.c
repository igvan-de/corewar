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
**	@brief:	write operation into .cor file
**
**	@param fd	:	.cor file descriptor
**	@param info	:	operation data
**
**	write_op writes the encode byte (if applicable)
**	and the operations' arguments into the .cor file.
**	the determined encode byte is parsed to determine
**	the format in which the arguments should be written.
*/

static	void	write_op(int fd, t_direction *info)
{
	static int		left[3] = {0, 2, 4};
	unsigned char	new;
	int				i;

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
			write_args(fd, new, info, i);
		i++;
	}
}

/*
** @brief writes executable champion commands in byte_code into filediscriptor
**
** @param fd = filediscripter to write string in
** @param info = struct with needed data for writing champ
*/

void			write_champ(int fd, t_direction *info)
{
	t_direction	*op_data;

	op_data = info;
	while (op_data != NULL)
	{
		if (0 < op_data->op_code && op_data->op_code < 17)
		{
			write(fd, &op_data->op_code, 1);
			write_op(fd, op_data);
		}
		op_data = op_data->next;
	}
}
