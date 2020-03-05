/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_tind.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 16:43:56 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/05 16:43:56 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	read and return a T_IND value from memory
*/

short	get_tind(t_env *env, int position)
{
	short ret;
	unsigned char byte;

	ret = 0;
	byte = env->map[modi(position)];
	ret |= (byte << 8);
	byte = env->map[modi(position + 1)];
	ret |= byte;
	return (ret);
}
