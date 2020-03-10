/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 14:42:06 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/10 14:42:06 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor	*dup_cursor(t_cursor *src, t_env *env)
{
	t_cursor *new;

	new = (t_cursor *)malloc(sizeof(t_cursor));
	if(!new)
		error_mem();
	new->carry = src->carry;
	new->op_code = 0;
	new->id = env->total_cursors;
	new->jump = src->jump;
	new->last_live = src->last_live;
	new->live_counter = src->live_counter;
	new->next = NULL;
	new->prev = NULL;
	new->registries = init_registries();
	cpy_reg_vals(new, src);
	new->wait_cycles = 0;
	return (new);
}