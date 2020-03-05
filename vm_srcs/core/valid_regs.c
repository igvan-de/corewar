/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_regs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 16:49:48 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/05 16:49:48 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	valid_regs checks each argument and if it is a T_REG,
**	checks if the value contained is a valid register number.
*/

int	valid_regs(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int arg_size_1;
	int arg_size_2;
	int arg_size_3;
	unsigned reg;

	arg_size_1 = get_arg_size(cursor->op_code, get_bit(encode, 0), get_bit(encode, 1));
	arg_size_2 = get_arg_size(cursor->op_code, get_bit(encode, 2), get_bit(encode, 3));
	arg_size_3 = get_arg_size(cursor->op_code, get_bit(encode, 4), get_bit(encode, 5));
	if (arg_size_1 == 1)
	{
		reg = env->map[modi(cursor->position + 2)];
		if (reg < 1 || 16 < reg)
			return (0);
	}
	if (arg_size_2 == 1)
	{
		reg = env->map[modi(cursor->position + arg_size_1 + 2)];
		if (reg < 1 || 16 < reg)
			return (0);
	}
	if (arg_size_3 == 1)
	{
		reg = env->map[modi(cursor->position + arg_size_1 + arg_size_2 + 2)];
		if (reg < 1 || 16 < reg)
			return (0);
	}
	return (1);
}
