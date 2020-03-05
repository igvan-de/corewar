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

/*
**	dump_movement prints the cursor movement to stdout
**	in four-digit hexidecimal.
*/

static	void	dump_movement(t_cursor *cursor, unsigned char bytes)
{
	ft_putstr("ADV ");
	ft_putnbr(bytes);
	ft_putstr(" (");
	fflush(stdout);
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

/*
**	dump_op prints a performed operation to stdout
**	if the -v 16 flag is enabled.
*/

void	dump_op(t_cursor *cursor, t_env *env)
{
	unsigned char bytes;

	bytes = 1;
	bytes += get_tdir_size(cursor->op_code);
	dump_movement(cursor, bytes);
	dump_bytes(cursor, env, bytes);
}

/*
**	dump_op_encode is an alternative version of dump_op
**	that is used with operations that have encoding bytes.
**	encoding byte and op_code are passed manually, because the
**	the cursor state might be overwritten by the execution of the
**	the last operation.
*/

void	dump_op_encode(t_cursor *cursor, t_env *env, unsigned char encode, unsigned char op_code)
{
	unsigned char bytes;

	bytes = 1;
	bytes += get_total_arg_size(op_code, encode);
	bytes++;
	dump_movement(cursor, bytes);
	dump_bytes(cursor, env, bytes);
}

/*
**	dump_op_invalid is an alternative version of dump_op that gets
**	called when an operation was found to be invalid.
*/

void	dump_op_invalid(t_cursor *cursor, t_env *env, unsigned char bytes)
{
	dump_movement(cursor, bytes);
	dump_bytes(cursor, env, bytes);
}