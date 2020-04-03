/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   insert_operation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:11:27 by mark           #+#    #+#                */
/*   Updated: 2020/04/03 04:22:25 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		insert_encode(t_direction *new, int i, int operation)
{
	static int shift[3] = {6, 4, 2};
	char bits; 
	
	bits = (char)operation;
	bits <<= shift[i];
	new->encode += bits;
}

void	process_kind(t_func_list *list, t_direction *new, int kind, int arg)
{
	if (list->line[list->line_char] >= '0' && list->line[list->line_char] <= '9')
	{
		if (kind & T_IND)
			return (process_t_ind(list, new, arg));
		else
			error_message(list, 89, 1, 8);
	}
	else if (list->line[list->line_char] == 'r')
	{
		if (kind & T_REG)
			return (process_t_reg(list, new, arg));
		else
			error_message(list, 88, 1, 8);
	}
	else if (list->line[list->line_char] == DIRECT_CHAR)
	{
		if (kind & T_DIR)
			return (process_t_dir(list, new, arg));
		else
			error_message(list, 87, 1, 8);
	}
	else
	{
		ft_printf("%c testing1\n", list->line[list->line_char]);
		ft_printf("%s testing2\n", list->line);
		error_message(list, 86, 2, 8);
	}
}

int		op_tab_info(int op_code, int section, int part)
{
	static	t_op	get_op[17] = {{{0}, 0, {0}, 0, 0, {0}, 0, 0},
		{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition r1 + r2 -> r3", 1, 0},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "subtraction r1 - r2 -> r3", 1, 0},
		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "and  r1&r2 -> r3", 1, 0},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "or   r1 | r2 -> r3", 1, 0},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "xor  r1^r2 -> r3", 1, 0},
		{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
		{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
		{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
		{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}};

	if (section == 0)
		return (get_op[op_code].nb_params);
	else if (section == 1)
		return (get_op[op_code].params_type[part]);
	return (-1);
}

void	insert_operation(t_func_list *list, t_direction *new)
{
	int i;
	int kind;
	int args;
	int	comma;

	i = 0;
	kind = 0;
	args = op_tab_info(new->op_code, 0, 0);
	comma = args - 1;
	while (i < args)
	{
		kind = 0;
		while (ft_isspace(list->line[list->line_char]) == 1)
			list->line_char++;
		kind = op_tab_info(new->op_code, 1, i);
		process_kind(list, new, kind, i);
		while (ft_isspace(list->line[list->line_char]) == 1)
			list->line_char++;
		if (comma != 0 && list->line[list->line_char] != ',')
			error_message(list, 80, 0, 8);
		list->line_char++;
		comma--;
		i++;
	}
	check_end_line(list);
}

