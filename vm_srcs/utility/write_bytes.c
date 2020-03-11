/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_bytes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 07:38:51 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/03 07:38:52 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void set_player_pos(t_cursor *cursor, t_env *env, int place)
{
	env->datamap[modi(place)].player = env->datamap[modi(cursor->position)].player;
	env->datamap[modi(place + 1)].player = env->datamap[modi(cursor->position)].player;
	env->datamap[modi(place + 2)].player = env->datamap[modi(cursor->position)].player;
	env->datamap[modi(place + 3)].player = env->datamap[modi(cursor->position)].player;
}

/*
**	get_byte receives a 4-byte value and returns the
**	byte indicated by the index provided as second argument.
*/

char	get_byte(int value, int index)
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
**	write_bytes receives a value and writes that value onto the
**	memory map at the position calculated by:
**
**	modi(cursor->position + rel_pos);
*/

void	write_bytes(int target_val, t_env *env, t_cursor *c, int rel_pos)
{
	int		place;
	char	byte;

	place = c->position + rel_pos;
	byte = get_byte(target_val, 0);
	env->map[modi(place)] = byte;
	byte = get_byte(target_val, 1);
	env->map[modi(place + 1)] = byte;
	byte = get_byte(target_val, 2);
	env->map[modi(place + 2)] = byte;
	byte = get_byte(target_val, 3);
	env->map[modi(place + 3)] = byte;
	set_player_pos(c, env, place);
}
