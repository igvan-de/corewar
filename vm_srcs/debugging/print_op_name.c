/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_op_name.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	print operation name
**
**	@param op_code	:	operation code
**	@param env		:	global environment struct
**
**	print_op_name receives a operation code and prints
**	the name of the operation the stdout.
*/

void	print_op_name(int op_code, t_env *env)
{
	t_op local_op;

	if (op_code <= 0 || op_code > 16)
	{
		ft_putendl("	could not find operation name --> is op_code correct?");
		return ;
	}
	local_op = env->op_tab[op_code];
	ft_putstr(local_op.name);
}
