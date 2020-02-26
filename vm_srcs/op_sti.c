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

static	unsigned char	get_arg_size(int op_code, int one, int two)
{
	if (one == 0 && two == 1)
		return (1);
	else if (one == 1 && two == 0)
		return (get_tdir_size(op_code));
	else if (one == 1 && two == 1)
		return (2);
	return (0);
}

static	int	validate_encode(unsigned char encode)
{
	int	one;
	int two;

//	printf("	validating encoding byte: \n");
//	print_bits(encode);
	one = get_bit(encode, 0);
	two = get_bit(encode, 1);
	if (one != 0 || two != 1)
		return (0);
	one = get_bit(encode, 4);
	two = get_bit(encode, 5);
	if (one == 1 && two == 1)
		return (0);
	one = get_bit(encode, 6);
	two = get_bit(encode, 7);
	if (one != 0 || two != 0)
		return (0);
//	printf("	sti encode byte is valid!\n");
	return (1);
}

static	int	count_regs(unsigned char encode)
{
	int one;
	int two;
	int regs;

//	printf("	counting regs in encoding byte: \n");
//	print_bits(encode);
	regs = 0;
	one = get_bit(encode, 0);
	two = get_bit(encode, 1);
	if (one == 0 && two == 1)
		regs++;
	one = get_bit(encode, 2);
	two = get_bit(encode, 3);
	if (one == 0 && two == 1)
		regs++;
	one = get_bit(encode, 4);
	two = get_bit(encode, 5);
	if (one == 0 && two == 1)
		regs++;
//	printf("	found %i regs\n", regs);
	return (regs);
}

static	int	validate_regs(t_cursor *cursor)
{
	unsigned char size_1;
	unsigned char size_2;
	unsigned char size_3;
	unsigned char encode;

	encode = *(cursor->position + 1);
	size_1 = get_arg_size(cursor->op_code, get_bit(encode, 0), get_bit(encode, 1));
	if (size_1 == 1)
	{
		if (*(cursor->position + 2) < 1 || 16  < *(cursor->position + 2))
			return (0);
	}
	size_2 = get_arg_size(cursor->op_code, get_bit(encode, 2), get_bit(encode, 3));
	if (size_2 == 1)
	{
		if (*(cursor->position + size_1 + 2) < 1 || 16  < *(cursor->position + size_1 + 2))
			return (0);
	}
	size_3 = get_arg_size(cursor->op_code, get_bit(encode, 4), get_bit(encode, 5));
	if (size_3 == 1)
	{
		if (*(cursor->position + size_1 + size_2 + 2) < 1 || 16  < *(cursor->position + size_1 + size_2 + 2))
			return (0);
	}
	return (1);
}

static	void	exec_sti(t_cursor *cursor)
{
	unsigned char encode;
	unsigned char	reg_num;
	unsigned short	arg_2_val;
	unsigned short	arg_3_val;
	unsigned char	target_val;
	unsigned int	rel_target_pos;

//	printf("	cursor %i is executing instruction sti for player: %i\n", cursor->id, cursor->registries[0] * -1);
	encode = *(cursor->position + 1);
	reg_num = *(cursor->position + 2);
//	printf("	target registry: %hhi\n", reg_num);
	arg_2_val = to_2bytes(*(cursor->position + 3), *(cursor->position + 4));
//	printf("	arg_2_val: %hi\n", arg_2_val);
	arg_3_val = to_2bytes(*(cursor->position + 5), *(cursor->position + 6));
//	printf("	arg_3_val: %hi\n", arg_3_val);
	target_val = cursor->registries[reg_num - 1];
//	printf("	target value: %hhi\n", target_val);
//	printf("	relative target_position: %u\n", (arg_2_val + arg_3_val) % IDX_MOD);
	rel_target_pos = (arg_2_val + arg_3_val) % IDX_MOD;
	*(cursor->position + rel_target_pos) = target_val;
	printf("	sti --> cursor %i wrote value: %hhi to address %p\n", cursor->id, target_val, cursor->position + rel_target_pos);
}

void	op_sti(t_cursor *cursor)
{
	int regs;

//	printf("	cursor %i is verifying instruction sti for player: %i\n", cursor->id, cursor->registries[0] * -1);
	if (validate_encode(*(cursor->position + 1)) == 0)
		return (move_cursor(cursor));
	regs = count_regs((*(cursor->position + 1)));
	if (regs > 0)
	{
		if (validate_regs(cursor) == 0)
			return (move_cursor(cursor));
	}
	exec_sti(cursor);
	move_cursor(cursor);
}