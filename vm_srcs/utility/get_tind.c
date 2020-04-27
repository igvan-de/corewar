/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_tind.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	read and return two bytes from memory
**
**	@param env	:	global environment structure
*/

short	get_tind(t_env *env, int position)
{
	short			ret;

	ret = to_2bytes(
			env->map[modi(position)],
			env->map[modi(position + 1)]);
	return (ret);
}
