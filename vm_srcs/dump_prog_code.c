/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_prog_code.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 18:16:03 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/19 18:16:04 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	print_arg_type takes two bit representations (one and two)
**	and prints the related argument type to stdout.
**	It also returns the argument size so that the parser can
**	jump to the next instruction.
*/

static	int	print_arg_type(int op_code, int one, int two)
{
	if (one == 0 && two == 1)
	{
		printf("	-->	ARG: T_REG\n");
		return (1);
	}
	else if (one == 1 && two == 0)
	{
		printf("	--> 	ARG: T_DIR\n");
		return (get_tdir_size(op_code));
	}
	else if (one == 1 && two == 1)
	{
		printf("	--> 	ARG: T_IND\n");
		return (2);
	}
	printf("	--> 	ARG: empty\n");
	return (0);
}	

/*
**	parse_encode_byte receives the encoding byte and the op_code
**	stored in the preceding byte. It then parses this byte
**	to determine the file types stored as operation arguments.
**	the last two bits are always zero.
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

static	int	parse_encode_byte(unsigned char octet, int op_code)
{
	int one;
	int two;
	int total_arg_size;

	total_arg_size = 0;
	one = get_bit(octet, 0);
	two = get_bit(octet, 1);
	total_arg_size += print_arg_type(op_code, one, two);
	one = get_bit(octet, 2);
	two = get_bit(octet, 3);
	total_arg_size += print_arg_type(op_code, one, two);
	one = get_bit(octet, 4);
	two = get_bit(octet, 5);
	total_arg_size += print_arg_type(op_code, one, two);
	return (total_arg_size);
}

/*
**	parse_instr receives the execution code and the current parse location
**	as index. It prints the operation at index and parses the following
**	encoding byte if necessary. Index gets adjusted to point to the next
**	instruction in the execution code.
*/

static	void	parse_instr(char *prog_code, unsigned *index, t_env *env)
{
	unsigned i;
	int op_code;

	i = *index;
	op_code = prog_code[i];
	print_op_name(op_code, env);
	if (op_code == 1 || op_code == 9 || op_code == 12)
		*index += get_tdir_size(op_code) + 1;
	else
		*index += parse_encode_byte(prog_code[i + 1], op_code) + 2;
}

/*
**	dump_prog_code takes a ptr to the champions execution code and
**	prints its instructions to stdout.
*/

void	dump_prog_code(char *prog_code, unsigned int prog_size, t_env *env)
{
	unsigned int i;

	ft_putstr("\n\n<------------------------- Welcome to CHAMPION CODE DUMP ---------------------->\n\n\n");

	i = 0;
	while (i < prog_size)
		parse_instr(prog_code, &i, env);
}
