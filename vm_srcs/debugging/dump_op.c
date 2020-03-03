/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_op.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 14:19:14 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/03 14:19:14 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	unsigned int	max_bytes(int op_code)
{
	if (op_code == 11 || op_code == 2)
		return (7);
	else if (op_code == 1)
		return (5);
	return (0);
}

void	dump_op(t_cursor *cursor, t_env *env)
{
	unsigned char bytes;
	unsigned int	i;

	bytes = 1;
	if (has_encode(cursor->op_code) == 1)
	{
		bytes += get_total_arg_size(cursor->op_code, env->map[modi(cursor->position + 1)]);
		bytes++;
	}
	else
		bytes += get_tdir_size(cursor->op_code);
	ft_putstr("ADV ");
	ft_putnbr(bytes);
	ft_putstr(" (");
	if (cursor->position != 0)
	{
		printf("%#06x -> %#06x) ", modi(cursor->position), modi(cursor->position + bytes));
		fflush(stdout);
	}
	else
	{
		printf("0x0000 -> %#06x) ", modi(cursor->position + bytes));
		fflush(stdout);
	}
	i = 0;
	while (i < bytes)
	{
		if (env->player_pos[modi(cursor->position + i)] != 0)
		{
			printf("%02x ", 0xFF & env->map[modi(cursor->position + i)]);
			fflush(stdout);
		}
		else
		{
			printf("%#02x ", env->map[modi(cursor->position + i)]);
			fflush(stdout);
		}
		i++;
	}
	ft_putchar('\n');
}

void	dump_op_size(t_cursor *cursor, t_env *env, unsigned char size)
{
	unsigned char bytes;
	unsigned int	i;

	bytes = 1;
	bytes += size;
	bytes++;
	ft_putstr("ADV ");
	if (bytes > max_bytes(cursor->op_code))
		ft_putnbr(max_bytes(cursor->op_code));
	else
		ft_putnbr(bytes);
	ft_putstr(" (");
	if (cursor->position != 0)
	{
		printf("%#06x -> %#06x) ", modi(cursor->position), modi(cursor->position + bytes));
		fflush(stdout);
	}
	else
	{
		printf("0x0000 -> %#06x) ", modi(cursor->position + bytes));
		fflush(stdout);
	}
	i = 0;
	while (i < bytes && i <= max_bytes(cursor->op_code))
	{
		if (env->player_pos[modi(cursor->position + i)] != 0)
		{
			printf("%02x ", 0xFF & env->map[modi(cursor->position + i)]);
			fflush(stdout);
		}
		else
		{
			printf("%#02x ", env->map[modi(cursor->position + i)]);
			fflush(stdout);
		}
		i++;
	}
	ft_putchar('\n');
}