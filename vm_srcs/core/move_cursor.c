/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_cursor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief: move the cursor to the next operation
**
**	@param env			:	global environment struct
**	@param c			:	target cursor
**
**	After an operation has been executed successfully, move_cursor
**	is called to move the target cursor to the next operation or the byte
**	after the last byte of the last operation. move_cursor is called after
**	successfull operations without an encoding byte.
*/

void	move_cursor(t_cursor *c, t_env *env)
{
	env->datamap[c->position].cursor = 0;
	if ((env->flag_byte & (1 << 2)) == (1 << 2))
		dump_op(c, env);
	c->position = modi(c->position + (get_tdir_size(c->op_code) + 1));
	env->datamap[c->position].cursor = 1;
	c->op_code = 0;
}

/*
**	@brief: move the cursor to the next operation
**
**	@param env			:	global environment struct
**	@param player_nb	:	target cursor
**	@param encode		:	last operation encoding byte
**	@param op_code		:	last operation operation code
**
**	move_cursor_encode is a version of move_cursor that gets called after
**	succesfull operations with an encode byte. It receives the encode byte
**	and op_code seperately because the execution of the last operation
**	could have overwritten them in memory.
*/

void	move_cursor_encode(t_cursor *c, t_env *env, t_byt encode, t_byt op_code)
{
	unsigned char	total_arg_size;

	env->datamap[c->position].cursor = 0;
	if ((env->flag_byte & (1 << 2)) == (1 << 2))
		dump_op_enc(c, env, encode, op_code);
	total_arg_size = get_total_arg_size(op_code, encode);
	c->position = modi(c->position + total_arg_size + 2);
	env->datamap[c->position].cursor = 1;
	c->op_code = 0;
}
