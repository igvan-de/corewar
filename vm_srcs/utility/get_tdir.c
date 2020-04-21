/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_tdir.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	read and return four bytes from memory
**
**	@param env	:	global environment structure
*/

int	get_tdir(t_env *env, int position)
{
	int					ret;

	ret = to_4bytes(
			to_2bytes(
				env->map[modi(position)],
				env->map[modi(position + 1)]),
			to_2bytes(
				env->map[modi(position + 2)],
				env->map[modi(position + 3)]));
	return (ret);
}
