/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_st.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 08:53:40 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/06 08:53:41 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	exec_st(t_cursor *cursor, t_env *env, unsigned char encode)
{
	unsigned char	src_reg;
	unsigned char	dst_reg;
	int				arg_2_size;
	int				val;
	int				rel_pos;

	src_reg = env->map[modi(cursor->position + 2)];
	val = cursor->registries[src_reg - 1];
	arg_2_size = get_arg_size(cursor->op_code, get_bit(encode, 2), get_bit(encode, 3));
	if (arg_2_size == 1)
	{
		dst_reg = env->map[modi(cursor->position + 3)];
		cursor->registries[dst_reg - 1] = val;
	}
	else if (arg_2_size == 2)
	{
		rel_pos = get_tind(env, cursor->position + 3) % IDX_MOD;
		write_bytes(val, env, cursor, rel_pos);
		if (-5 < cursor->registries[0] && cursor->registries[0] < 0)
		{
			env->player_pos[modi(cursor->position + rel_pos)] = cursor->registries[0] * -1;
			env->player_pos[modi(cursor->position + rel_pos + 1)] = cursor->registries[0] * -1;
			env->player_pos[modi(cursor->position + rel_pos + 2)] = cursor->registries[0] * -1;
			env->player_pos[modi(cursor->position + rel_pos + 3)] = cursor->registries[0] * -1;
		}
	}
	else 
		error_exec(3);
}

void			op_st(t_cursor *cursor, t_env *env)
{
	unsigned char op_code;
	unsigned char encode;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, encode, env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));
	exec_st(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}