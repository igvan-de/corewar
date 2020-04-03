/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_cmp_op.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 11:24:17 by mlokhors       #+#    #+#                */
/*   Updated: 2020/04/03 03:04:04 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		cmp_op(uint64_t *hash_table, uint64_t number)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (hash_table[i] == number)
			return (i + 1);
		i++;
	}
	return (-1);
}
/*
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
*/
/*
** calculate
*/

int		calc_cmp_operation(t_func_list *list, int j)
{
	uint64_t total;
	int op;

	op = 0;
	total = calc_hash(list->line + list->line_char, j - list->line_char);
//	total = line_hash(list,list->line + list->line_char , j);
	op = cmp_op(list->hash_table, total);
	return (op);
}