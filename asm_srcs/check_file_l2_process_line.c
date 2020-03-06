/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l2_process_line.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 05:22:10 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/06 14:14:20 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	because it can contain as many spaces we split it up in a double array
**	ft_strplit need to be worked on to split it on a , aswell but only one
**	,, is error
*/

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
}

int		insert_encode(t_direction *new, int i, int operation)
{
	static int shift[4] = {0, 6, 4, 2};
	int i;
	char bits = (char)operation;

	i = 0;
	bits << shift[i];
	new->encode += bits;
}

int		check_label_char(char c)
{
	int i;

	i = 0;
	while (i < 35)
	{
		if (c == LABEL_CHARS[i])
			return (0);
		i++;
	}
	return (-1);
}

int		fill_t_ind(t_func_list *list, t_direction *new, char *line, int arg)
{
	int i;

	i = list->line_char;
	insert_encode(new, arg, 3);
	while ()
}

int		cmp_line(t_func_list *list, t_direction *new, char *line, int arg)
{
	int dir;

	dir = op_tab_info(new->op_code, 1, arg);
	if (line[list->line_char] >= '0' && line[list->line_char] <= '9')
	{
		if (dir & T_IND)
			return (fill_t_ind(list, new, line, arg));
		else
			return (40);
	}
	else if (line[list->line_char] == 'r')
	{
		if (dir & T_REG)
			return (fill_t_reg(list, new, line, arg));
		else
			return (41);
	}
	else if (line[list->line_char] == DIRECT_CHAR)
	{
		if (dir & T_DIR)
			return (fill_t_dir(list, new, line, arg));
		else
			return (42);
	}
}

void	insert_operation(t_func_list *list, t_direction *new, char *line)
{
	int ret;
	int i;
	int arg;
	int	dir;

	ret = 0;
	i = 0;
	dir = 0;
	arg = op_tab_info(new->op_code, 0, 0);
	while (i < arg)
	{
		while (ft_isspace(line[list->line_char]) == 1)
			list->line_char++;
		dir = op_tab_info(new->op_code, 1, i + 1);
		cmp_line_op(list, new, line, i + 1);
		i++;
	}
}


void	get_label_name(t_func_list *list, t_direction *new, char *line, int j)
{
	int i;
	int start;
	int ret;

	i = 0;
	start = list->line_char;
	ret = 0;
	while (list->line_char < j)
	{
		ret = check_label_char(line[list->line_char]);
		if (ret == -1)
			return (error_messege(list, 100, 0));
		list->line_char++;
	}
	new->label = ft_strsub(line, start, j - start);
	if (new->label == NULL)
		return (error_messege(list, 8, 2));
	list->line_char = j;
}

void	insert_info_into_node(t_func_list *list, char *line,
		t_direction *new, t_count counter)
{
	int j;
	int ret;
	int number;

	ret = 0;
	j = 0;
	while (ft_isspace(line[list->line_char]) == 1)
		list->line_char++;
	j = list->line_char;
	while (ft_isspace(line[j]) == 0)
		j++;
	if (line[j - 1] == LABEL_CHAR)
		get_label_name(list, new, line, j);
	while (ft_isspace(line[j]) == 1)
		j++;	
	if (j > 5)
		return (error_messege(list, 102, 0));
	number = calc_cmp_operation(list, line, j);
	if (number == -1)
		return (error_messege(list, 101, 0));
	new->op_code = number;
	list->line_char = j;
	insert_operation(list, new, line);
}

void	insert_file_node(t_func_list *list, char *line)
{
	int j;
	int ret;
	t_count counter;
	t_direction *new;

	counter.byte_count = 0;
	counter.i = 0;
	new = NULL;
	add_instruction_node(list, new, &counter);
	insert_info_into_node(list, line, new, counter);
}

void	process_line_into_list(t_func_list *list, char *line)
{
	while (ft_isspace(line[list->line_char]) == 1)
		list->line_char++;
	if (line[list->line_char] == '.')
	{
		list->line_char++;
		get_name_or_comment(list, line);
	}
	else
		insert_file_node(list, line);
}