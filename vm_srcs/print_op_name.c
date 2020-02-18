/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_op_name.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 13:24:02 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/18 13:24:05 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_op_name(t_env *env, int op_id)
{
	int i;
	t_op curr_op;

	i = 0;
	while (i < 16)
	{
		curr_op = env->op_tab[i];
		if (curr_op.id == op_id)
			return (ft_putendl(curr_op.name));
		i++;
	}
	ft_putendl("error: could not find op with given id");
}