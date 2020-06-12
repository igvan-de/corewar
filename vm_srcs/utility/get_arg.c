/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_arg.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	determine argument size
**
**	@param op_code	:	operation code
**
**	get_size receives an argument type and returns the size of that
**	that argument type.
*/

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

/*
**	@brief:	read the argument value from memory
**
**	@param c		:	target cursor
**	@param env		:	global environment struct
**	@param type 	:	argument type
**	@param rel_pos	:	relative position
**
**	get_val is called by get_arg after the type of the argument has been
**	determined. depending on the type, get_val will either read a registry
**	value or read 4 or 2 bytes from memory. The rel_pos position is used
**	to indicate target read location relative to the current position
**	of the cursor.
*/

static	int				get_val(t_cursor *c, t_env *e, t_byt type, int rel_pos)
{
	t_byt	reg_num;
	int		addr;

	addr = modi(c->position + rel_pos);
	if (type == REG_CODE)
	{
		reg_num = e->map[addr];
		return (c->registries[reg_num]);
	}
	else if (type == DIR_CODE && get_tdir_size(c->op_code) == 4)
		return (get_tdir(e, addr));
	else if (type == DIR_CODE && get_tdir_size(c->op_code) == 2)
		return (get_tind(e, addr));
	else if (type == IND_CODE)
	{
		rel_pos = get_tind(e, addr);
		rel_pos %= IDX_MOD;
		return (get_tdir(e, c->position + rel_pos));
	}
	error_exec(4);
	return (-1);
}

/*
**	@brief:	retrieve an argument value
**
**	@param c		:	target cursor
**	@param env		:	global environment struct
**	@param encode	:	encode byte
**	@param num		:	argument index
**
**	get_arg is a versatile utility function which is used by various
**	operation functions to retrieve argument values. The function
**	interprets the encode byte to determine which type of argument
**	it should get. It uses get_type to determine the type of the argument
**	and get_size to determine the size. The num value is used to indicate
**	which argument should be returned.
*/

int						get_arg(t_cursor *c, t_env *env, t_byt encode, int num)
{
	unsigned char type;
	unsigned char rel_pos;

	type = get_type(encode, 1);
	rel_pos = 2;
	if (num == 1)
		return (get_val(c, env, type, 2));
	rel_pos += get_size(c->op_code, type);
	type = get_type(encode, 2);
	if (num == 2)
		return (get_val(c, env, type, rel_pos));
	rel_pos += get_size(c->op_code, type);
	type = get_type(encode, 3);
	if (num == 3)
		return (get_val(c, env, type, rel_pos));
	error_exec(4);
	return (-1);
}
