/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_fork.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 10:00:12 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/06 10:00:13 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_lfork(t_cursor *cursor, t_env *env)
{
	short		addr;
	t_cursor	*new_cursor;

	addr = get_tind(env, modi(cursor->position + 1));
	(env->total_cursors)++;
	new_cursor = dup_cursor(cursor, env);
	new_cursor->position = modi(cursor->position + addr);
	push_cursor(new_cursor, &env->cursor_stack);
	move_cursor(cursor, env);
}
