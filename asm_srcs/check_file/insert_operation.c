/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   insert_operation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:11:27 by mark          #+#    #+#                 */
/*   Updated: 2020/05/06 15:39:29 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief	makes the encode byte for operation node
**
** @param	new = memory adress from a new or existing list.
**			it always has the last node in the list
**			this list contains all the information for a operation
** @param	i = a number that contains bitwise the possible argument types
** @param	operation = the type of an operation argument
** @param	new->encode = the total argument and type stored in a char
**
** this is a function that registry the arguments type and
** place them in encode byte of the node
** based on the iteration it decide how many bytes it need to shift
** operation exist out of 2 bits;
**	T_REG = 01 = 1
**	T_DIR = 10 = 2
**	T_IND = 11 = 3
**	it will be stored in a single char which are 8 bits.
**	from left to right the first 2 bits are the first argument
** 	the following 2 is for the second argument
**	the next 2 is for the 3rd argument and the last 2 are just empty
*/

void		insert_encode(t_direction *new, int i, int operation)
{
	static int	shift[3] = {6, 4, 2};
	char		bits;

	bits = (char)operation;
	bits <<= shift[i];
	new->encode += bits;
}

/*
** @brief	checks if the amount of argument of a operation
**
** @param	list = the container where we store all our information
** @param	new = memory adress from a new or existing list.
**			it always has the last node in the list
**			this list contains all the information for a operation
** @param	kind = a number that contains bitwise the possible argument types
** @param	arg = which argument number it is
**
** it compares the input is the same as the argument type: variable kind
** if the input is not the same as the argument type then its an error
*/

static void	process_kind(t_func_list *list, t_direction *new, int kind, int arg)
{
	if (list->line[list->line_char] == 'r')
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
	else if (kind & T_IND)
		return (process_t_ind(list, new, arg));
	else
		error_message(list, 86, 2, 8);
}

/*
** @brief	search for argument amount and arguments type
**
** @param	op_code = code of operation
** @param	section =  is to decide which we need to return
**			argument amount or argument type
** @param	part = is for which argument type need to be returned
**			based on the index;
**
** this is a one of the resources we haven been given from school
*/

static int	op_tab_info(int op_code, int section, int part)
{
	static	t_op	get_op[17] = {{{0}, 0, {0}, 0, 0, {0}, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, " ", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, " ", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, " ", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, " ", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, " ", 1, 0},
	{"and", 3, {ALL, ALL, T_REG}, 6, 6, " ", 1, 0},
	{"or", 3, {ALL, ALL, T_REG}, 7, 6, " ", 1, 0},
	{"xor", 3, {ALL, ALL, T_REG}, 8, 6, " ", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, " ", 0, 1},
	{"ldi", 3, {ALL, T_DIR | T_REG, T_REG}, 10, 25, " ", 1, 1},
	{"sti", 3, {T_REG, ALL, T_DIR | T_REG}, 11, 25, " ", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, " ", 0, 1},
	{"lld", 2, {T_IND | T_DIR, T_REG}, 13, 10, " ", 1, 0},
	{"lldi", 3, {ALL, T_DIR | T_REG, T_REG}, 14, 50, " ", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, " ", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, " ", 1, 0}};

	if (section == 0)
		return (get_op[op_code].nb_params);
	else
		return (get_op[op_code].params_type[part]);
}

/*
** @brief	checks if the amount of argument of a operation
**
** @param	list = the container where we store all our information
** @param	new = memory adress from a new or existing list.
**			it always has the last node in the list
**			this list contains all the information for a operation
** @param	comma = keep track of the amount of ','
** @param	i = which argument needs to be filled in
** kind is a number that contains all possible arguments of that operation
** it will keeps track of the comma amount aswell
*/

static void	l_insert_operation(t_func_list *list, t_direction *new,
		int comma, int i)
{
	int kind;

	kind = 0;
	skip_space(list);
	kind = op_tab_info(new->op_code, 1, i);
	process_kind(list, new, kind, i);
	skip_space(list);
	if (comma == 0 && list->line[list->line_char] == ',')
		error_message(list, 80, 0, 8);
	if (list->line[list->line_char] != '\0'
		&& list->line[list->line_char + 1] != '\0' && comma != 0)
		list->line_char += 1;
}

/*
** @brief	checks if the amount of argument of a operation
**
** @param	list = the container where we store all our information
** @param	new = memory adress from a new or existing list.
**			it always has the last node in the list
**			this list contains all the information for a operation
**
** it checks how many arguments are possible for each operation.
*/

void		insert_operation(t_func_list *list, t_direction *new)
{
	int i;
	int args;
	int	comma;

	i = 0;
	args = op_tab_info(new->op_code, 0, 0);
	comma = args - 1;
	while (i < args)
	{
		l_insert_operation(list, new, comma, i);
		comma--;
		i++;
	}
	check_end_line(list);
}
