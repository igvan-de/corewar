/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_cmp_op.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 11:24:17 by mlokhors      #+#    #+#                 */
/*   Updated: 2020/04/15 03:01:15 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** here its calcuate the operation hash and
** compares with the operation hash table
*/

static int	cmp_op(uint64_t *hash_table, uint64_t number)
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

int			calc_cmp_operation(t_func_list *list, int j)
{
	uint64_t	total;
	int			op;

	op = 0;
	total = calc_hash(list->line + list->line_char, j);
	op = cmp_op(list->hash_table, total);
	return (op);
}
