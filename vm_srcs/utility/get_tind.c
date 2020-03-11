/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_tind.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 16:43:56 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:28:20 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

short	get_tind(t_env *env, int position)
{
	short			ret;

	ret = to_2bytes(
			env->map[modi(position)],
			env->map[modi(position + 1)]);
	return (ret);
}
