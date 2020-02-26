/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_ld.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 16:18:53 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 16:18:54 by jdunnink      ########   odam.nl         */
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
	int one;
	int two;

	one = get_bit(encode, 0);
	two = get_bit(encode, 1);
	if (one == 0 && two == 1)
		return (0);
	one = get_bit(encode, 2);
	two = get_bit(encode, 3);
	if (one != 0 || two != 1)
		return (0);
	one = get_bit(encode, 4);
	two = get_bit(encode, 5);
	if (one != 0 || two != 0)
		return (0);
	one = get_bit(encode, 6);
	two = get_bit(encode, 7);
	if (one != 0 || two != 0)
		return (0);	
	return (1);
}

static	void	exec_ld(t_cursor *cursor, unsigned char arg_1_size, unsigned char reg_num)
{
	int t_dir_value;
	short t_ind_value;
	int type_flag;
	int rel_target_addr;

	type_flag = 0;
	if (arg_1_size == 4)
	{
		type_flag = 1;
		t_dir_value = *(int *)(cursor->position + 2);
	}
	else if (arg_1_size == 2)
	{
		t_ind_value = *(short *)(cursor->position + 2);
		type_flag = 0;
	}
	if (type_flag == 0)
	{
		rel_target_addr = t_ind_value % IDX_MOD;
		t_dir_value = (int)*(cursor->position + rel_target_addr);
	}
	printf("	ld --> reading value %i into registry %i of cursor %i\n", t_dir_value, reg_num, cursor->id);
	cursor->registries[reg_num - 1] = t_dir_value;
	if (t_dir_value == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	printf("	ld --> carry for cursor %i is set to %i\n", cursor->id, cursor->carry);
}

void	op_ld(t_cursor *cursor)
{
	unsigned char encode;
	unsigned char arg_size_1;
	unsigned char reg_num;

	encode = *(cursor->position + 1);
	if (validate_encode(encode) == 0)
		return (move_cursor(cursor));
	arg_size_1 = get_arg_size(cursor->op_code, get_bit(encode, 0), get_bit(encode, 1));
	reg_num = *(cursor->position + arg_size_1 + 2);
	if (reg_num < 1 || 16 < reg_num)
		return (move_cursor(cursor));
	exec_ld(cursor, arg_size_1, reg_num);
	move_cursor(cursor);
}