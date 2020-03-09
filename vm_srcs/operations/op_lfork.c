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

static	void	cpy_reg_vals(t_cursor *new, t_cursor *src)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
		new->registries[i] = src->registries[i];
		i++;
	}
}

static	int					*init_registries(void)
{
	int	i;
	int	*new_regs;

	new_regs = (int *)malloc(sizeof(int) * (REG_NUMBER));
	if (!new_regs)
		error_mem();
	i = 0;
	while (i < REG_NUMBER)
	{
		new_regs[i] = 0;
		i++;
	}
	return (new_regs);
}

static	t_cursor	*dup_cursor(t_cursor *src, t_env *env)
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

static	void				push_cursor(t_cursor *c, t_cursor **stack)
{
	if (*stack == NULL)
		*stack = c;
	else
	{
		c->next = *stack;
		(*stack)->prev = c;
		*stack = c;
	}
}

void	op_lfork(t_cursor *cursor, t_env *env)
{
	short addr;
	t_cursor *new_cursor;

	addr = to_2bytes(env->map[modi(cursor->position + 1)], env->map[modi(cursor->position + 2)]);
	(env->total_cursors)++;
	new_cursor = dup_cursor(cursor, env);
	push_cursor(new_cursor, &env->cursor_stack);
	new_cursor->position = modi(cursor->position + addr);
	move_cursor(cursor, env);
}