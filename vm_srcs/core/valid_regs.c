/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_regs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 16:49:48 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:22:56 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief: validate register numbers
**
**	@param c		:	current cursor
**	@param env	 	:	global environment struct
**	@param encode	:	encoding byte	
**
**	valid_regs receives a cursor and its encoding byte
**	and checks if the register numbers at the current  cursor position
**	are valid. A valid register number is between 1 and 16.
**	The function returns true if the register numbers are valid. Otherwise,
**	the function returns false.
*/

int	valid_regs(t_cursor *c, t_env *env, unsigned char encode)
{
	int			size_1;
	int			size_2;
	int			size_3;
	unsigned	reg;

	size_1 = get_arg_size(c->op_code, get_bit(encode, 0), get_bit(encode, 1));
	size_2 = get_arg_size(c->op_code, get_bit(encode, 2), get_bit(encode, 3));
	size_3 = get_arg_size(c->op_code, get_bit(encode, 4), get_bit(encode, 5));
	if (size_1 == 1)
	{
		reg = env->map[modi(c->position + 2)];
		if (reg < 1 || 16 < reg)
			return (0);
	}
	if (size_2 == 1)
	{
		reg = env->map[modi(c->position + size_1 + 2)];
		if (reg < 1 || 16 < reg)
			return (0);
	}
	if (size_3 == 1)
	{
		reg = env->map[modi(c->position + size_1 + size_2 + 2)];
		if (reg < 1 || 16 < reg)
			return (0);
	}
	return (1);
}
