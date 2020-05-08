/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_arg_s.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 11:27:35 by igor          #+#    #+#                 */
/*   Updated: 2020/05/02 20:54:35 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

/*
** @brief
**
** @param fd_s		= file discriptor to write operations(arguments) in
** @param i			= index of byte
** @param arg_size	= size of operation(argument)
** @param file		= struct containing all data
**
** by converting the executable we know what is the value on current byte,
** by running itoa over it we convert it into a string the write is down
** with ft_putstr_fd into filediscriptor.
** checking what type it is, provides us the information to know what type
** of operation(argument) we need to write into filediscriptor and the format:
**
** T_REG needs 'r' char before operation(argument)
** T_IND needs nothing char before operation(argument)
** T_DIR needs '%' char before operation(argument)
*/

static	void	write_arg(int fd_s, int i, int arg_size, t_file *file)
{
	int				value;
	char			*executable;

	value = convert(i, file->exec, arg_size);
	ft_asprintf(&executable, "%i", value);
	if (file->type == REG)
	{
		ft_putchar_fd(' ', fd_s);
		ft_putchar_fd('r', fd_s);
		ft_putstr_fd(executable, fd_s);
	}
	else if (file->type == IND)
	{
		ft_putchar_fd(' ', fd_s);
		ft_putstr_fd(executable, fd_s);
	}
	else if (file->type == DIR)
	{
		ft_putchar_fd(' ', fd_s);
		ft_putchar_fd('%', fd_s);
		ft_putstr_fd(executable, fd_s);
	}
	ft_memdel((void **)&executable);
}

/*
** @brief
**
** @param fd_s		= file discriptor to write operations(arguments) in
** @param i			= index on bytes
** @param file		= struct containing all data
** @param op_code	= value of op_code
** @return int		= sizes of arg 1, 2 & 3
**
** parse encode byte is jumped two indexes on bytes, because we want to skip
** the encode. but we need to know the octect for get_bit
** by looping trough all operations(arguments), we can see what their value is
** meaning what their size and type is, so we can write them in filediscripter
*/

static	int		parse_encbyte(int fd_s, int i, t_file *f, int op_code)
{
	int				arg_value_1;
	int				arg_value_2;
	int				arg_value_3;
	unsigned char	oct;

	oct = f->exec[i - 1];
	arg_value_1 = get_arg_value(f, op_code, get_bit(oct, 0), get_bit(oct, 1));
	write_arg(fd_s, i, arg_value_1, f);
	i += arg_value_1;
	arg_value_2 = get_arg_value(f, op_code, get_bit(oct, 2), get_bit(oct, 3));
	if (arg_value_2 != 0)
		ft_putchar_fd(',', fd_s);
	write_arg(fd_s, i, arg_value_2, f);
	i += arg_value_2;
	arg_value_3 = get_arg_value(f, op_code, get_bit(oct, 4), get_bit(oct, 5));
	if (arg_value_3 != 0)
		ft_putchar_fd(',', fd_s);
	write_arg(fd_s, i, arg_value_3, f);
	return (arg_value_1 + arg_value_2 + arg_value_3);
}

/*
** @brief
**
** @param fd_s		= file discriptor to write operations(arguments) in
** @param op_code	= value of op_code
** @param file		= struct containing all data
**
** by  first checking if the op_code has a correct value,
** we can later write it into the filediscripter
*/

static	void	write_op(int fd_s, int op_code, t_file *file)
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

/*
** @brief
**
** @param fd_s		= file discriptor to write operations(arguments) in
** @param index		= index of byte
** @param file		= struct containing all data
**
** checking the current place of byte index provides what the op_code is,
** by checking the value of the op_code we know how many operations(arguments)
** we could expect, so also how many places from the current index we need to
** jump to go to the first argument. Because all op_code values have
** an encode after the op_code, except for the op_code values 1, 9, 12 & 15
*/

static	void	write_str(int fd_s, unsigned int *index, t_file *file)
{
	unsigned int	i;
	int				op_code;

	i = *index;
	op_code = file->exec[i];
	write_op(fd_s, op_code, file);
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
	{
		file->type = DIR;
		write_arg(fd_s, i + 1, get_tdir_size(op_code), file);
		*index += get_tdir_size(op_code) + 1;
	}
	else
		*index += parse_encbyte(fd_s, i + 2, file, op_code) + 2;
	ft_putstr_fd("\n", fd_s);
}

/*
** @brief loops through all bits of executable code
**
** @param fd_s		= file discriptor to write operations(arguments) in
** @param prog_size	= size of executable code
** @param file		= struct containing all data
**
** by looping with an index through the bytes we can write all operations
** by giving the address we stay at the correct byte index
*/

void			write_args_into_s(int fd_s, unsigned prog_size, t_file *file)
{
	unsigned int	i;

	i = 0;
	while (i < prog_size)
		write_str(fd_s, &i, file);
}
