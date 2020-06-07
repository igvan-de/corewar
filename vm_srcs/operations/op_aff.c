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

static	void	exec_aff(t_cursor *cursor, t_env *env, t_byt encode)
{
	t_byt	reg_num;
	int		ascii;

	reg_num = get_reg_num(cursor, env, encode, 1);
	if ((env->flag_byte & (1 << 4)) == (1 << 4))
	{
		ascii = cursor->registries[reg_num];
		if (ft_isprint(ascii) == 1)
			ft_printf("Aff: %c\n", (char)ascii);
	}
}

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

void			op_aff(t_cursor *cursor, t_env *env)
{
	unsigned char op_code;
	unsigned char encode;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, encode, env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));
	exec_aff(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}
