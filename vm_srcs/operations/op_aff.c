/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_aff.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_aff(t_cursor *cursor, t_env *env)
{
	char	reg_num;
	char	ascii;

	reg_num = env->map[modi(cursor->position + 1)];
	if (1 <= reg_num && reg_num <= 16)
	{
		if ((env->flag_byte & (1 << 4)) == (1 << 4))
		{
			ascii = (char)cursor->registries[reg_num - 1];
			if (ft_isprint((int)ascii) == 1)
				ft_printf("%c\n", ascii);
		}
		move_cursor(cursor, env);
	}
	else
		invalid_op(cursor, env, 1);
}
