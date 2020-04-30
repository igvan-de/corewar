/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_arg_s.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 11:27:35 by igor          #+#    #+#                 */
/*   Updated: 2020/04/30 12:54:16 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

static const char	*get_op(unsigned int op_code, t_file *file)
{
	t_op	local_op;

	if (op_code <= 0 || op_code > 16)
	{
		ft_printf("Could not find operation code\n");
		exit(-1);
	}
	local_op = file->op_tab[op_code];
	return((const char*)local_op.name);
}

static void	write_op(int fd, unsigned int *index, t_file *file)
{
	unsigned int	i;
	const char		*op_code;

	i = *index;
	op_code = get_op(file->args[i], file);
	ft_putstr_fd(op_code, fd);
	ft_putchar_fd(' ', fd);
}

void		write_arg_s(int fd, unsigned prog_size, t_file *file)
{
	unsigned int	i;

	i = 0;
	while (i < prog_size)
		write_op(fd, &i ,file);
}
