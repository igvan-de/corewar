/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_op.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 14:19:14 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 17:20:19 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	dump_movement prints the cursor movement to stdout
**	in four-digit hexidecimal.
*/

static	void	dump_movement(t_cursor *cursor, unsigned char bytes)
{
	ft_putstr("ADV ");
	ft_putnbr(bytes);
	ft_putstr(" (");
	if (cursor->position != 0)
		ft_printf("%#06x -> %#06x) ", modi(cursor->position), modi(cursor->position + bytes));
	else
		ft_printf("0x0000 -> %#06x) ", modi(cursor->position + bytes));
}

/*
**	dump_bytes prints the bytes related to the last operation
**	to stdout in two digit hexidecimal.
*/

static	void	dump_bytes(t_cursor *cursor, t_env *env, unsigned char bytes)
{
	unsigned int i;

	i = 0;
	while (i < bytes)
	{
		if (env->datamap[modi(cursor->position + i)].player != 0)
			ft_printf("%02x ", 0xFF & env->map[modi(cursor->position + i)]);
		else
			ft_printf("%#02x ", env->map[modi(cursor->position + i)]);
		i++;
	}
	ft_putchar('\n');
}

void			dump_op(t_cursor *cursor, t_env *env)
{
	unsigned char bytes;

	bytes = 1;
	bytes += get_tdir_size(cursor->op_code);
	dump_movement(cursor, bytes);
	dump_bytes(cursor, env, bytes);
}

void			dump_op_encode(t_cursor *cursor, t_env *env, unsigned char encode, unsigned char op_code)
{
	unsigned char bytes;

	bytes = 1;
	bytes += get_total_arg_size(op_code, encode);
	bytes++;
	dump_movement(cursor, bytes);
	dump_bytes(cursor, env, bytes);
}

void			dump_op_invalid(t_cursor *cursor, t_env *env, unsigned char bytes)
{
	dump_movement(cursor, bytes);
	dump_bytes(cursor, env, bytes);
}
