/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_op.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	print program counter movement
**
**	@param c		:	target cursor
**	@param bytes	:	movement size in bytes
**
**	dump_movement is a debug function that can be used to print
**	program counter movement of the cursor passed as parameter. dump_movement
**	is also called when operation verbosity is enabled.
*/

static	void	dump_movement(t_cursor *c, unsigned char bytes)
{
	ft_putstr("ADV ");
	ft_putnbr(bytes);
	ft_putstr(" (");
	if (c->position != 0)
		ft_printf("%#06x -> %#06x) ",
		modi(c->position), modi(c->position + bytes));
	else
		ft_printf("0x0000 -> %#06x) ", modi(c->position + bytes));
}

/*
**	@brief:	print operation bytes
**
**	@param cursor	:	target cursor
**	@param env		:	global environment struct
**	@param bytes	:	operation size in bytes
**
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

/*
**	@brief:	print operation and PC movement
**
**	@param cursor	:	target cursor
**	@param env		:	global environment struct
**
**	dump_op prints operation bytes and PC movement to stdout.
**	gets called when operation verbosity is enabled.
*/

void			dump_op(t_cursor *cursor, t_env *env)
{
	unsigned char bytes;

	bytes = 1;
	bytes += get_tdir_size(cursor->op_code);
	dump_movement(cursor, bytes);
	dump_bytes(cursor, env, bytes);
}

/*
**	@brief:	print operation and PC movement
**
**	@param c		:	target cursor
**	@param env		:	global environment struct
**	@param enc		:	operation encode byte
**	@param op_code	:	operation code
**
**	dump_op prints operation bytes and PC movement to stdout.
**	gets called when operation verbosity is enabled.
**
**	version of dump_op for operations with an encode byte
*/

void			dump_op_enc(t_cursor *c, t_env *env, t_byt enc, t_byt op_code)
{
	t_byt bytes;

	bytes = 1;
	bytes += get_total_arg_size(op_code, enc);
	bytes++;
	dump_movement(c, bytes);
	dump_bytes(c, env, bytes);
}

/*
**	@brief:	print operation and PC movement
**
**	@param c		:	target cursor
**	@param env		:	global environment struct
**	@param bytes	:	operation size in bytes
**
**	dump_op prints operation bytes and PC movement to stdout.
**	gets called when operation verbosity is enabled.
**
**	version of dump_op for invalid operations
*/

void			dump_op_invalid(t_cursor *c, t_env *env, t_byt bytes)
{
	dump_movement(c, bytes);
	dump_bytes(c, env, bytes);
}
