/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_arg_value.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/02 17:17:46 by igor          #+#    #+#                 */
/*   Updated: 2020/05/02 17:18:17 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

static int	get_bit(unsigned char octet, int index)
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

int			get_arg_value(t_file *file, int op_code, int one, int two)
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
