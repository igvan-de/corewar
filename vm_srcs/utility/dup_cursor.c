/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	duplicate a cursor
**
**	@param src	:	source cursor
**	@param env	:	global environment struct
**
**	duplicate a cursor. This function is used in fork and lfork
**	to create duplicate cursors. The new cursor has all the same values
**	as its parent and is pushed unto the top of the cursor_stack.
*/

t_cursor	*dup_cursor(t_cursor *src, t_env *env)
{
	t_cursor *new;

	new = (t_cursor *)malloc(sizeof(t_cursor));
	if (!new)
		error_mem();
	new->carry = src->carry;
	new->op_code = src->op_code;
	new->id = env->total_cursors;
	new->jump = src->jump;
	new->last_live = src->last_live;
	new->live_counter = src->live_counter;
	new->next = NULL;
	new->prev = NULL;
	new->registries = init_registries();
	cpy_reg_vals(new, src);
	new->wait_cycles = src->wait_cycles;
	return (new);
}
