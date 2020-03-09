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

int	get_tdir(unsigned char op_code, t_env *env, int position)
{
	int					ret;
	int					size;

	ret = 0;
	size = get_tdir_size(op_code);
	if (size == 2)
		ret = to_2bytes(env->map[modi(position)],
						env->map[modi(position + 1)]);
	else
		ret = to_4bytes(
				to_2bytes(
					env->map[modi(position)],
					env->map[modi(position + 1)]),
				to_2bytes(
					env->map[modi(position + 2)],
					env->map[modi(position + 3)]));
	return (ret);
}
