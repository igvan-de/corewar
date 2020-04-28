/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_reg_num.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	retrieve a register number from memory
**
**	@param cursor	: target cursor
**	@param env		: global environment structure
**	@param encode	: encode byte
**	@param arg_num	: argument index
**
**	get_reg_num can be used to read a register number from memory.
**	If an argument is a T_REG, get_reg_num is used by operation functions
**	to read the number of the register from memory. The arg_num variable
**	is used to indicate which argument should be targeted.
*/

int	get_reg_num(t_cursor *cursor, t_env *env, t_byt encode, int arg_num)
{
	int place;

	place = modi(cursor->position + 2);
	if (arg_num > 1)
		place += get_arg_size(cursor->op_code,
			get_bit(encode, 0), get_bit(encode, 1));
	if (arg_num > 2)
		place += get_arg_size(cursor->op_code,
			get_bit(encode, 2), get_bit(encode, 3));
	return ((int)env->map[modi(place)]);
}
