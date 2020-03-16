/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_op_name.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 13:24:02 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 17:21:12 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_op_name(int op_code, t_env *env)
{
	t_op local_op;

	if (op_code <= 0 || op_code > 16)
		ft_putendl("	could not find operation name --> is op_code correct?");
	local_op = env->op_tab[op_code];
	ft_putstr(local_op.name);
}
