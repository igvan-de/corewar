/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_exec_code.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	print operation argument type to stdout
**
**	@param op_code		:	current operation code
**	@param one			:	first bit of argument bitpair
**	@param two			:	second bit of argument bitpair
**
**	print_arg_type takes two bit representations (one and two)
**	and prints the related argument type to stdout.
**	It also returns the argument size so that the parser can
**	jump to the next instruction.
*/

static	int		print_arg_type(int op_code, int one, int two)
{
	if (one == 0 && two == 1)
	{
		ft_putstr("	T_REG	");
		return (1);
	}
	else if (one == 1 && two == 0)
	{
		ft_putstr("	T_DIR	");
		return (get_tdir_size(op_code));
	}
	else if (one == 1 && two == 1)
	{
		ft_putstr("	T_IND	");
		return (2);
	}
	return (0);
}

/*
**	@brief:	print operation arguments to stdout
**
**	@param index		:	current byte index
**	@param arg_size 	:	size of target argument
**	@param prog_code	:	ptr to execution code
**
**	print_arg_val receives the champion execution code as prog_code,
**	an index pointing at an instruction argument, and the size of that
**	argument as arg_size. The function then prints the value contained
**	within that argument. Works for arguments with type: T_DIR / T_IND / T_REG.
*/

static	void	print_arg_val(int index, int arg_size, char *prog_code)
{
	if (arg_size == 1)
		ft_putnbr(prog_code[index]);
	else if (arg_size == 2)
		ft_putnbr(to_2bytes(prog_code[index], prog_code[index + 1]));
	else if (arg_size == 4)
	{
		ft_putnbr(
			to_4bytes(
				to_2bytes(
					prog_code[index], prog_code[index + 1]),
				to_2bytes(
					prog_code[index + 2], prog_code[index + 3])));
	}
}

/*
**	@brief:	local encoding byte parser
**
**	@param i		:	current byte index
**	@param exec 	:	ptr to execution code
**	@param oct		:	encode byte
**	@param op_code	:	current operation code
**
**	parse_encode_byte receives the encoding byte and the op_code
**	stored in the preceding byte. It then parses this byte
**	to determine the file types stored as operation arguments.
**	Finally, it prints out the argument type, as well as the value
**	contained, through calls to print_arg_type and print_arg_val.
**
**	example:
**
**	binary encoding byte: 10110100
**
** 		first arg | second arg | third arg | last
**			10			11			01			00
**			T_DIR		T_IND		T_REG		empty
**
**	size:	2 or 4		2			1			0
*/

static	int		parse_encbyte(int i, char *exec, unsigned char oct, int op_code)
{
	int	arg_size_1;
	int arg_size_2;
	int arg_size_3;

	ft_putstr("	");
	print_bits(oct);
	arg_size_1 = print_arg_type(op_code, get_bit(oct, 0), get_bit(oct, 1));
	print_arg_val(i, arg_size_1, exec);
	arg_size_2 = print_arg_type(op_code, get_bit(oct, 2), get_bit(oct, 3));
	i += arg_size_1;
	print_arg_val(i, arg_size_2, exec);
	arg_size_3 = print_arg_type(op_code, get_bit(oct, 4), get_bit(oct, 5));
	i += arg_size_2;
	print_arg_val(i, arg_size_3, exec);
	return (arg_size_1 + arg_size_2 + arg_size_3);
}

/*
**	@brief:	local execution code parser
**
**	@param exec		:	ptr to execution code
**	@param index 	:	ptr to current index within execution code
**	@param env		:	global environment struct
**
**	parse_instr receives the execution code and the current parse location
**	as index. It prints the operation at index and parses the following
**	encoding byte if necessary. Index gets adjusted to point to the next
**	instruction in the execution code.
*/

static	void	parse_instr(char *exec, unsigned *index, t_env *env)
{
	unsigned	i;
	int			op_code;

	i = *index;
	op_code = exec[i];
	print_op_name(op_code, env);
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
	{
		ft_putstr("			T_DIR	");
		print_arg_val(i + 1, get_tdir_size(op_code), exec);
		*index += get_tdir_size(op_code) + 1;
	}
	else
		*index += parse_encbyte(i + 2, exec, exec[i + 1], op_code) + 2;
	ft_putchar('\n');
}

/*
**	@brief:	print a players' execution code to stdout
**
**	@param exec			:	ptr to execution code
**	@param prog_size 	:	execution code size in bytes
**	@param env			:	global environment struct
**
**	dump_exec_code is a debug function that can be used to
**	print a players' execution code to stdout in human readable
**	format.
*/

void			dump_exec_code(char *exec, unsigned int prog_size, t_env *env)
{
	unsigned int i;

	ft_putstr("\n\n<------ EXECUTION CODE DUMP ------->\n\n\n");
	i = 0;
	while (i < prog_size)
		parse_instr(exec, &i, env);
}
