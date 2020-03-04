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

/*
**	move_cursor receives a cursor and moves the position
**	to the next operation. If the -v 16 flag is enabled,
**	the operation details are printed to stdout.
*/

void	move_cursor(t_cursor *cursor, t_env *env)
{
	if ((env->flag_byte & (1 << 2)) == (1 << 2))
		dump_op(cursor, env);
	cursor->position = modi(cursor->position + (get_tdir_size(cursor->op_code) + 1));
	cursor->op_code = 0;
}

/*
**	move_cursor_encode is an alternative version of move_cursor
**	that gets called in operations that have a valid encoding byte.
*/

void	move_cursor_encode(t_cursor *cursor, t_env *env, unsigned char encode, unsigned char op_code)
{
	unsigned char	total_arg_size;

	if ((env->flag_byte & (1 << 2)) == (1 << 2))
		dump_op_encode(cursor, env, encode, op_code);
	total_arg_size = get_total_arg_size(op_code, encode);
	cursor->position = modi(cursor->position + total_arg_size + 2);
	cursor->op_code = 0;
}
