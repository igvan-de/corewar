/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_bytes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	mark player position at written bytes in memory
**
**	@param cursor	:	target cursor
**	@param env		:	global environment struct
**	@param place	:	target position in memory
**
**	after a value is written into memory, set_player_pos marks
**	the player who wrote the bytes by copying the player number
**	from the source instruction.
*/

static	void	set_player_pos(t_cursor *cursor, t_env *env, int place)
{
	env->datamap[modi(place)].player =
		env->datamap[modi(cursor->position)].player;
	env->datamap[modi(place + 1)].player =
		env->datamap[modi(cursor->position)].player;
	env->datamap[modi(place + 2)].player =
		env->datamap[modi(cursor->position)].player;
	env->datamap[modi(place + 3)].player =
		env->datamap[modi(cursor->position)].player;
}

/*
**	@brief:	extract a byte from a four byte number
**
**	@param value	:	four byte number
**	@param index	:	index of target byte
**
**	get_byte receives a 4-byte value and returns the
**	byte indicated by the index provided as second argument.
*/

char			get_byte(int value, int index)
{
	if (index == 0)
		return ((char)(value >> 24));
	if (index == 1)
		return ((char)(value >> 16));
	if (index == 2)
		return ((char)(value >> 8));
	if (index == 3)
		return ((char)value);
	error_exec(2);
	return (-1);
}

/*
**	@brief:	write four bytes to memory
**
**	@param val		:	value to write
**	@param env		:	global environment struct
**	@param c		:	target cursor
**	@param rel_pos	:	relative position
**
**	write_bytes is used by operation functions to write values into memory.
*/

void			write_bytes(int val, t_env *env, t_cursor *c, int rel_pos)
{
	int		place;
	char	byte;

	place = c->position + rel_pos;
	byte = get_byte(val, 0);
	env->map[modi(place)] = byte;
	byte = get_byte(val, 1);
	env->map[modi(place + 1)] = byte;
	byte = get_byte(val, 2);
	env->map[modi(place + 2)] = byte;
	byte = get_byte(val, 3);
	env->map[modi(place + 3)] = byte;
	set_player_pos(c, env, place);
}
