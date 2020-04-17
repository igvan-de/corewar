/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_reg_num.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 08:30:52 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/10 08:30:52 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	get_reg_num(t_cursor *cursor, t_env *env, unsigned char encode, int arg_num)
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
