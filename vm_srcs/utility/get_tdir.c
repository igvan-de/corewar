/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_tdir.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 16:38:42 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/05 16:38:43 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	read and return a T_DIR value from memory
*/

int	get_tdir(t_env *env, int position)
{
	int ret;
	unsigned char byte;

	ret = 0;
	byte = env->map[modi(position)];
	ret |= (byte << 24);
	byte = env->map[modi(position + 1)];
	ret |= (byte << 16);
	byte = env->map[modi(position + 2)];
	ret |= (byte << 8);
	byte = env->map[modi(position + 3)];
	ret |= byte;
	return (ret);
}
