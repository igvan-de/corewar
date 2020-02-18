/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 08:46:02 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/18 08:46:39 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	print_op_name(t_env *env)
{
	int i;
	t_op curr_op;

	i = 0;
	while (i < 16)
	{
		curr_op = env->op_tab[i];
		ft_putendl(curr_op.name);
		i++;
	}
}

int main(void)
{
	t_env env;
	ft_putstr("Welcome to Corewar!\n");
	
	load_optab(&env);
	print_op_name(&env);
	return (0);
}
