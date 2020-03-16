/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_tdir.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 16:38:42 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:28:03 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
