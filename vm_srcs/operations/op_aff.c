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

/*
**	@brief:	print a byte if it is a writable character.
**
**	@param cursor		:	target cursor
**	@param env 			:	global environment struct
**
**	op_aff is an operation function which can be used to
**	print the character stored in a register to stdout.
**	the character only gets printed if it is a writable character
**	and if the -a flag is enabled. op_aff is flag dependent because
**	it can interfere with the ncurses visualizer.
*/

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
