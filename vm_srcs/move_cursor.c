/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_cursor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 16:25:33 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 16:25:33 by jdunnink      ########   odam.nl         */
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

static	int	has_encode(unsigned char op_code)
{
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
		return (0);
	return (1);
}

void	move_cursor(t_cursor *cursor)
{
	unsigned char encode;
	unsigned char total_arg_size;
	int		encode_flag;

	encode_flag = 0;
	if (has_encode(cursor->op_code) == 1)
		encode_flag = 1;
	if (encode_flag == 1)
	{
		encode = *(cursor->position + 1);
		total_arg_size = 0;
		total_arg_size += get_arg_size(cursor->op_code, get_bit(encode, 0), get_bit(encode, 1));
		total_arg_size += get_arg_size(cursor->op_code, get_bit(encode, 2), get_bit(encode, 3));
		total_arg_size += get_arg_size(cursor->op_code, get_bit(encode, 4), get_bit(encode, 5));
		cursor->position += total_arg_size + 2;
	}
	else
		cursor->position += (get_tdir_size(cursor->op_code) + 1);
	cursor->op_code = 0;
	printf("	cursor %i is jumping to next address %p which contains op_code: %hhi\n", cursor->id, cursor->position, *(cursor->position));
}
