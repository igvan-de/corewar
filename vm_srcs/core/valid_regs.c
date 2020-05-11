/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_regs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
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

static	int	check_reg(t_env *env, t_cursor *c, int index)
{
	unsigned reg;

	reg = env->map[modi(c->position + index)];
	if (reg < 1 || REG_NUMBER < reg)
		return (0);
	return (1);
}

int			valid_regs(t_cursor *c, t_env *env, t_byt encode)
{
	int			size_1;
	int			size_2;
	int			size_3;

	size_1 = get_arg_size(c->op_code, get_bit(encode, 0), get_bit(encode, 1));
	size_2 = get_arg_size(c->op_code, get_bit(encode, 2), get_bit(encode, 3));
	size_3 = get_arg_size(c->op_code, get_bit(encode, 4), get_bit(encode, 5));
	if (size_1 == 1 && check_reg(env, c, 2) == 0)
		return (0);
	if (size_2 == 1 && check_reg(env, c, size_1 + 2) == 0)
		return (0);
	if (size_3 == 1 && check_reg(env, c, size_1 + size_2 + 2) == 0)
		return (0);
	return (1);
}
