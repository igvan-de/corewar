/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l2_process_line.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/07 17:54:15 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/27 04:16:09 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#include <stdio.h>

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
	return (-1);
}

int		insert_encode(t_direction *new, int i, int operation)
{
	static int shift[3] = {6, 4, 2};
	int j;
	char bits = (char)operation;

	i = 0;
	bits << shift[i];
	new->encode += bits;
}

static bool		check_label_char(char c)
{
	int i;

	i = 0;
	while (i < 35)
	{
		if (c == LABEL_CHARS[i])
			return (true);
		i++;
	}
	return (false);
}

int		process_args(t_direction *new, int arg, int conv, char *str)
{
	if (str != NULL)
		return (ft_memmove(new->arg_str[arg], str, ft_strlen(str)));
	else
	{
		new->arg_num[arg] = conv;
	}
}

int		get_dir_size(int op_code)
{
	const int dir_size[16] = {4, 4, 4, 4, 4, 4, 4, 4,
	2, 2, 2, 2, 4, 2, 2, 4};

	return (dir_size[op_code - 1]);
}

int		process_t_ind(t_func_list *list, t_direction *new, int arg)
{
	int converted;

	list->total_bytes += 2;
	new->byte_size += 2;
	converted = ft_atoill(list->line + list->line_char);
	insert_encode(new, arg, 2);
	process_args(new, arg, converted, NULL);
}

int		process_t_reg(t_func_list *list, t_direction *new,int arg)
{
	int converted;

	list->total_bytes += 1;
	new->byte_size += 1;
	list->line_char++;
	converted = ft_atoill(list);
	insert_encode(new, arg, 1);
	ft_atoi(list->line + list->line_char);
}

int		process_t_dir(t_func_list *list, t_direction *new, int arg)
{
	int dir_size;
	int converted;

	dir_size =  get_dir_bytes(new->op_code);
	new->byte_size += dir_size;
	list->total_bytes += dir_size;
	insert_encode(new, arg, 3);
	converted = ft_atoill(list->line + list->line_char);
	ft_atoi(list->line + list->line_char);
}

int		process_kind(t_func_list *list, t_direction *new, int kind, int arg)
{
	if (list->line[list->line_char] >= '0' && list->line[list->line_char] <= '9')
	{
		if (kind & T_IND)
			return (process_t_ind(list, new, arg));
		else
			error_message(list, 0, 0);
	}
	else if (list->line[list->line_char] == 'r')
	{
		if (kind & T_REG)
			return (process_t_reg(list, new, arg));
		else
			error_message(list, 0, 0);
	}
	else if (list->line[list->line_char] == DIRECT_CHAR)
	{
		if (kind & T_DIR)
			return (process_t_dir(list, new, arg));
		else
			error_message(list, 0, 0);
	}
}

void	insert_operation(t_func_list *list, t_direction *new)
{
	int i;
	int kind;
	int args;

	i = 0;
	kind = 0;
	args = op_tab_info(new->op_code, 0, 0);
	while (i < args)
	{
		kind = 0;
		while (ft_isspace(list->line[list->line_char]) == 1)
			list->line_char++;
		kind = op_tab_info(new->op_code, 1, i);
		process_kind(list, new, kind, i);
		while (ft_isspace(list->line[list->line_char]) == 1)
			list->line_char++;
		i++;
	}
}

void	get_label_name(t_func_list *list, t_direction *new, int len)
{
	int start;
	int ret;

	start = list->line_char;
	ret = 0;
	while (list->line_char < len)
	{
		ret = check_label_char(list->line[list->line_char]);
		if (ret == -1)
			error_message(list, 100, 0);
		list->line_char++;
	}
	new->label = ft_strsub(list->line, start, len);
	if (new->label == NULL)
		error_message(list, 8, 2);
	list->line_char = len;
}

int		if_encode(int op_code)
{
	const int	encode[16] = {1, 2, 2, 2, 2, 2, 2, 2, 1,
	2, 2, 1, 2, 2, 1, 2};

	return (encode[op_code - 1]);
}

void	check_operation(t_func_list *list,
		t_direction *new, int i)
{
	int number;
	int len;
	int op_encode;

	op_encode = 0;
	number = 0;
	len = i - list->line_char;
	if (len > 5 || len <= 0)
		error_message(list, 103, 0);
	number = calc_cmp_operation(list, len);
	if (number == -1)
		error_message(list, 101, 0);
	new->op_code = number;
	op_encode = if_encode(number);
	list->total_bytes += op_encode;
	new->byte_size += op_encode;
	list->line_char = i;
}

void	check_sort(t_func_list *list,
		t_direction *new, int i)
{
	while (ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
	i = list->line_char;
	while (list->line[i] && ft_isspace(list->line[i]) == 0)
		i++;
	if (list->line[i - 1] == LABEL_CHAR)
	{
		if (new->label != NULL)
			error_message(list, 102, 0);
		get_label_name(list, new, i);
		list->line_char = i;
		return (check_sort(list, new, i));
	}
	else
		check_operation(list, new, i);
}

void	insert_info_into_node(t_func_list *list,
		t_direction *new, int last_index)
{
	int i;

	last_index *= 2;
	i = 0;
	check_sort(list, new, i);
	insert_operation(list, new);
}

void	insert_file_node(t_func_list *list)
{
	int last_index;
	t_direction *new;

	last_index = 0;
	new = NULL;
	add_instruction_node(list, &new, &last_index);
	insert_info_into_node(list, new, last_index);
	list->total_bytes += new->byte_size;
}

void	process_line_into_list(t_func_list *list)
{
	while (ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
	if (list->line[list->line_char] == '.')
	{
		list->line_char++;
		get_name_or_comment(list);
	}
	else if(list->name != NULL)
		insert_file_node(list);
	else
		error_message(list, 0, 0);	
}
