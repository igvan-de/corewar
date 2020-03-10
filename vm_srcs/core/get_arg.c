/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_sti.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 11:04:59 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 11:04:59 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	unsigned char	get_size(unsigned char op_code, unsigned char type)
{
	if (type == REG_CODE)
		return (1);
	else if (type == DIR_CODE)
		return (get_tdir_size(op_code));
	else if (type == IND_CODE)
		return (2);
	error_exec(4);
	return (-1);
}

static	int	get_val(t_cursor *cursor, t_env *env, unsigned char type, int rel_pos)
{
	unsigned char reg_num;
	int addr;

	addr = modi(cursor->position + rel_pos);
	if (type == REG_CODE)
	{
		reg_num = env->map[addr];
		return(cursor->registries[reg_num - 1]);
	}
	else if (type == DIR_CODE)
		return (get_tdir(cursor->op_code, env, addr));
	else if (type == IND_CODE)
	{
		rel_pos = get_tind(env, addr);
		return (get_tdir(cursor->op_code, env, cursor->position + rel_pos));
	}
	error_exec(4);
	return (-1);
}

int	get_arg(t_cursor *cursor, t_env *env, unsigned char encode, int arg_num)
{
	unsigned char type;
	unsigned char rel_pos;

	type = get_type(encode, 1);
	rel_pos = 2;
	if (arg_num == 1)
		return (get_val(cursor, env, type, 2));
	rel_pos += get_size(cursor->op_code, type);
	type = get_type(encode, 2);
	if (arg_num == 2)
		return (get_val(cursor, env, type, rel_pos));
	rel_pos += get_size(cursor->op_code, type);
	type = get_type(encode, 3);
	if (arg_num == 3)
		return (get_val(cursor, env, type, rel_pos));
	error_exec(4);
	return (-1);
}