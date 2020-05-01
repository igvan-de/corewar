/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_arg_s.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 11:27:35 by igor          #+#    #+#                 */
/*   Updated: 2020/05/01 15:17:46 by igor          ########   odam.nl         */
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

int convert(unsigned char *s, int size)
{
	int				i;
	unsigned int	temp;

	i = 0;
	temp = 0;
	while (i < size)
	{
		temp = temp << 8;
		temp |= s[i];
		i++;
	}
	if (size == 1)
		return ((char)temp);
	else if (size == 2)
		return ((short)temp);
	return ((int)temp);
}

static	int		get_arg_size(int op_code, int one, int two)
{
	if (one == 0 && two == 1)
		return (1);
	else if (one == 1 && two == 0)
		return (get_tdir_size(op_code));
	else if (one == 1 && two == 1)
		return (2);
	return (0);
}

static void	write_arg(int fd, int arg_size, char *exec)
{
	int				value;
	const char		*executable;

	value = convert((unsigned char*)exec, arg_size);
	executable = ft_itoa(value);
	ft_printf("arg_size = %d\n", arg_size);
	ft_printf("value = %d\n", value);
	ft_printf("exec = %s\n", executable);
	if (arg_size == 1)
	{
		ft_putstr_fd("test1", fd);
		ft_putchar_fd('r', fd);
		ft_putstr_fd(executable ,fd);
	}
	else if (arg_size == 2)
	{
		ft_putstr_fd("test2", fd);
		ft_putstr_fd(executable ,fd);
	}
	else
	{
		ft_putstr_fd("test3", fd);
		ft_putchar_fd('%', fd);
		ft_putstr_fd(executable ,fd);
	}
}

static	int		parse_encbyte(int fd, char *exec, unsigned char oct, int op_code)
{
	int	arg_size_1;
	int arg_size_2;
	int arg_size_3;

	arg_size_1 = get_arg_size(op_code, get_bit(oct, 0), get_bit(oct, 1));
	write_arg(fd, arg_size_1, exec);
	arg_size_2 = get_arg_size(op_code, get_bit(oct, 2), get_bit(oct, 3));
	write_arg(fd, arg_size_2, exec);
	arg_size_3 = get_arg_size(op_code, get_bit(oct, 4), get_bit(oct, 5));
	write_arg(fd, arg_size_3, exec);
	return (arg_size_1 + arg_size_2 + arg_size_3);
}

static void	write_op(int fd, int op_code ,t_file *file)
{
	t_op			local_op;

	if (op_code <= 0 || op_code > 16)
	{
		ft_printf("Could not find operation code\n");
		exit(-1);
	}
	local_op = file->op_tab[op_code];
	ft_putstr_fd((const char*)local_op.name, fd);
	ft_putchar_fd(' ', fd);
}

static void	write_str(int fd, unsigned int *index, t_file *file)
{
	unsigned int	i;
	int				op_code;
	char			*exec;

	i = *index;
	exec = file->exec_code;
	op_code = exec[i];
	write_op(fd, op_code, file);
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
	{
		write_arg(fd, get_tdir_size(op_code), exec);
		*index += get_tdir_size(op_code) + 1;
	}
	else
		*index += parse_encbyte(i + 2, exec, exec[i + 1], op_code) + 2;
	ft_putstr_fd("\n", fd);
}

void		write_arg_s(int fd, unsigned prog_size, t_file *file)
{
	unsigned int	i;

	i = 0;
	while (i < prog_size)
		write_str(fd, &i, file);
}
