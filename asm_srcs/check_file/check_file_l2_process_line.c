/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l2_process_line.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/07 17:54:15 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/17 06:43:46 by mark          ########   odam.nl         */
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

/* dit is een bool functie, maakt het stuk makkelijker om code te lezen.
** true = 1, false = 0. Je moet even kijken wat je zelf fijner vind, maar ik ben voorstander van bool
*/
// bool		check_label_char(char c)
// {
// 	int i;

// 	i = 0;
// 	while (i < 35)
// 	{
// 		if (c == LABEL_CHARS[i])
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

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
	int i;
	int args;

	i = 0;
	args = op_tab_info(new->op_code, 0, 0);
	while (i < args)
	{
		while (ft_isspace(line[list->line_char]) == 1)
			list->line_char++;
		dir = op_tab_info(new->op_code, 1, i + 1); //wat doen we verder met dir?
		cmp_line_op(list, new, line, i + 1);
		i++;
	}
}

void	get_label_name(t_func_list *list, t_direction *new, char *line, int len)
{
	int i;
	int start;
	int ret;

	i = 0;
	start = list->line_char;
	ret = 0;
	while (list->line_char < len)
	{
		ret = check_label_char(line[list->line_char]);
		if (ret == -1)
			error_message(list, 100, 0);
		list->line_char++;
	}
	new->label = ft_strsub(line, start, len);
	if (new->label == NULL)
		error_message(list, 8, 2);
	list->line_char = len;
}

void	check_operation(t_func_list *list, char *line,
		t_direction *new, int i)
{
	int number;
	int len;

	number = 0;
	len = list->line_char - i;
	if (len > 5 || len <= 0)
		error_message(list, 103, 0);
	number = calc_cmp_operation(list, line, len);
	if (number == -1)
		error_message(list, 101, 0);
	new->op_code = number;
	list->line_char = i;
}

void	check_sort(t_func_list *list, char *line,
		t_direction *new, int i)
{
	while (ft_isspace(line[list->line_char]) == 1)
		list->line_char++;
	i = list->line_char;
	while (ft_isspace(line[i]) == 0)
		i++;
	if (line[i - 1] == LABEL_CHAR)
	{
		if (new->label != NULL)
			error_message(list, 102, 0);
		get_label_name(list, new, line, i);
		list->line_char = i;
		return (check_sort(list, line, new, i));
	}
	else
		check_operation(list, line, new, i);
}

void	insert_info_into_node(t_func_list *list, char *line,
		t_direction *new, int last_index)
{
	int i;

	i = 0;
	check_sort(list, line, new, i);
	insert_operation(list, new, line);
}

void	insert_file_node(t_func_list *list, char *line)
{
	int ret;
	int last_index;
	t_direction *new;

	last_index = 0;
	new = NULL;
	add_instruction_node(list, new, &last_index);
	insert_info_into_node(list, line, new, last_index);
	list->total_bytes += new->byte_size;
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
