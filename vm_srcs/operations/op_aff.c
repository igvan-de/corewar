/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_aff.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 09:57:08 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:19:25 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    op_aff(t_cursor *cursor, t_env *env)
{
    char    reg_num;

    reg_num = env->map[modi(cursor->position + 1)];
    if (1 <= reg_num && reg_num <= 16)
    {
//        ft_putchar(cursor->registries[reg_num - 1]);
//        ft_putchar('\n');
        move_cursor(cursor, env);
    }
    else
        invalid_op(cursor, env, 1);
}