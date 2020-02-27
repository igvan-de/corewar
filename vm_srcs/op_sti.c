/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_sti.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 11:04:59 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 11:04:59 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	validate_regs checks each argument of the cursor's current
**	position and, if it is a T_REG, checks if the value stored
**	is a valid register number.
*/

static	int		validate_regs(t_cursor *cursor)
{
	unsigned char size_1;
	unsigned char size_2;
	unsigned char size_3;
	unsigned char encode;

	encode = *(cursor->position + 1);
	size_1 = get_arg_size(cursor->op_code, get_bit(encode, 0), get_bit(encode, 1));
	if (size_1 == 1)
	{
		if (*(cursor->position + 2) < 1 || 16 < *(cursor->position + 2))
			return (0);
	}
	size_2 = get_arg_size(cursor->op_code, get_bit(encode, 2), get_bit(encode, 3));
	if (size_2 == 1)
	{
		if (*(cursor->position + size_1 + 2) < 1 || 16 < *(cursor->position + size_1 + 2))
			return (0);
	}
	size_3 = get_arg_size(cursor->op_code, get_bit(encode, 4), get_bit(encode, 5));
	if (size_3 == 1)
	{
		if (*(cursor->position + size_1 + size_2 + 2) < 1 || 16 < *(cursor->position + size_1 + size_2 + 2))
			return (0);
	}
	return (1);
}

/*
**	exec_sti retrieves the needed values from the memory map
**	in relation to the current position of the cursor, and executes
**	the sti operation with the values found.
*/

static	void	exec_sti(t_cursor *cursor)
{
	unsigned char	encode;
	unsigned char	reg_num;
	unsigned short	arg_2_val;
	unsigned short	arg_3_val;
	unsigned char	target_val;
	unsigned int	rel_target_pos;

	encode = *(cursor->position + 1);
	reg_num = *(cursor->position + 2);
	arg_2_val = to_2bytes(*(cursor->position + 3), *(cursor->position + 4));
	arg_3_val = to_2bytes(*(cursor->position + 5), *(cursor->position + 6));
	target_val = cursor->registries[reg_num - 1];
	rel_target_pos = (arg_2_val + arg_3_val) % IDX_MOD;
	*(cursor->position + rel_target_pos) = target_val;
	printf("	sti --> cursor %i wrote value: %hhi to address %p\n", cursor->id, target_val, cursor->position + rel_target_pos);
}

/*
**	op_sti executes the operation sti at the current position
**	of the cursor passed as parameter. It receives a register number
**	as first argument, and writes the value stored in that register
**	to the relative address calculated as a result of:
**
**	cursor->position + (SECOND_ARGUMENT + THIRD_ARGUMENT % IDX_MOD);
**
**	if the encoding byte or the register numbers are invalid, the function
**	moves the cursor to the next operation by calling move_cursor.
*/

void			op_sti(t_cursor *cursor, t_env *env)
{
	int regs;

	if (valid_encode(cursor->op_code, *(cursor->position + 1), env) == 0)
		return (move_cursor(cursor));
	regs = count_registers((*(cursor->position + 1)));
	if (regs > 0)
	{
		if (validate_regs(cursor) == 0)
			return (move_cursor(cursor));
	}
	exec_sti(cursor);
	move_cursor(cursor);
}
