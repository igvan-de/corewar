/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l2_3_calc_cmp_op.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 11:24:17 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/11 16:05:48 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		cmp_op(int *hash_table, int number)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (hash_table[i] == number)
			return (i + 1);
	}
	return (-1);
}

int		line_hash(t_func_list *list, char *operation, int len)
{
	int total;
	int i;

	i = 0;
	total = 0;
	while (*operation != '\0' && i < len)
	{
		total += till_power(*operation, i);
		list->line_char++;
		operation++;
		i++;
	}
	return (total);
}

/*
** calculate
*/

int		calc_cmp_operation(t_func_list *list, char *line, int j)
{
	int total;
	int op;

	op = 0;
	total = line_hash(list, line, j);
	op = cmp_op(list->hash_table, total);
	if (op == -1)
		error_message();
	return (op);
}
