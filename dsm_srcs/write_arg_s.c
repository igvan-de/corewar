/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_arg_s.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 11:27:35 by igor          #+#    #+#                 */
/*   Updated: 2020/05/02 14:34:31 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

int	get_bit(unsigned char octet, int index)
{
	int shift_right;

	if (index < 0 || index > 8)
		return (-1);
	shift_right = 7;
	octet = octet << index;
	octet = octet >> shift_right;
	if ((1 & octet) == 1)
		return (1);
	return (0);
}

static	int		get_arg_value(t_file *file, int op_code, int one, int two)
{
	if (one == 0 && two == 1)
	{
		file->type = REG;
		return (1);
	}
	else if (one == 1 && two == 0)
	{
		file->type = DIR;
		return (get_tdir_size(op_code));
	}
	else if (one == 1 && two == 1)
	{
		file->type = IND;
		return (2);
	}
	file->type = NONE;
	return (0);
}

static void	write_arg(int fd_s, int i, int arg_size, t_file *file)
{
	int				value;
	const char		*executable;

	ft_printf("arg_size = %d\n", arg_size);
	value = convert(i, file->exec, arg_size);
	ft_printf("value = %d\n", value);
	executable = (const char*)ft_itoa(value);
	if (file->type == REG)
	{
		ft_putchar_fd(' ', fd_s);
		ft_putstr_fd("REG ", fd_s);
		ft_putchar_fd('r', fd_s);
		ft_putstr_fd(executable ,fd_s);
	}
	else if (file->type == IND)
	{
		ft_putchar_fd(' ', fd_s);
		ft_putstr_fd("IND||DIR ", fd_s);
		ft_putstr_fd(executable ,fd_s);
	}
	else if (file->type == DIR)
	{
		ft_putchar_fd(' ', fd_s);
		ft_putstr_fd("DIR ", fd_s);
		ft_putchar_fd('%', fd_s);
		ft_putstr_fd(executable ,fd_s);
	}
}

static	int		parse_encbyte(int fd_s, int i, t_file *file, int op_code)
{
	int				arg_value_1;
	int				arg_value_2;
	int				arg_value_3;
	unsigned char	oct;

	oct = file->exec[i + 1];
	arg_value_1 = get_arg_value(file, op_code, get_bit(oct, 0), get_bit(oct, 1));
	write_arg(fd_s, i, arg_value_1, file);
	arg_value_2 = get_arg_value(file, op_code, get_bit(oct, 2), get_bit(oct, 3));
	write_arg(fd_s, i, arg_value_2, file);
	arg_value_3 = get_arg_value(file, op_code, get_bit(oct, 4), get_bit(oct, 5));
	write_arg(fd_s, i, arg_value_3, file);
	return (arg_value_1 + arg_value_2 + arg_value_3);
}

static void	write_op(int fd_s, int op_code ,t_file *file)
{
	t_op			local_op;

	if (op_code <= 0 || op_code > 16)
	{
		ft_printf("Could not find operation code\n");
		exit(-1);
	}
	local_op = file->op_tab[op_code];
	ft_putstr_fd((const char*)local_op.name, fd_s);
}

static void	write_str(int fd_s, unsigned int *index, t_file *file)
{
	unsigned int	i;
	int				op_code;
	// char			*exec;

	i = *index;
	// exec = file->exec_code;
	op_code = file->exec[i];
	write_op(fd_s, op_code, file);
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
	{
		file->type = DIR;
		write_arg(fd_s, i, get_tdir_size(op_code), file);
		*index += get_tdir_size(op_code) + 1;
	}
	else
		*index += parse_encbyte(fd_s, i, file, op_code) + 2;
	ft_putstr_fd("\n", fd_s);
}

void		write_arg_s(int fd_s, unsigned prog_size, t_file *file)
{
	unsigned int	i;

	i = 0;
	while (i < prog_size)
		write_str(fd_s, &i, file);
}
