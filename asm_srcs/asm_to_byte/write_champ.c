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


static void	write_op(int fd, t_direction *info)
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
			write_args(fd, new, info, i);
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
		write_op(fd, probe);
		probe = probe->next;
	}
}
