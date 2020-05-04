/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_cmp_op.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 11:24:17 by mlokhors      #+#    #+#                 */
/*   Updated: 2020/05/04 02:22:30 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief	compare possible hash operation with hash table
**
** @param	hash_table = hash table of operations
** @param	number = possible operation
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

/*
** @brief	calculate possible operation and compare them in hash table
**
** @param	list = the container where we store all our information
** @param	len = length of possible operation
*/

int			calc_cmp_op(t_func_list *list, int len)
{
	uint64_t	total;
	int			op;

	op = 0;
	total = calc_hash(list->line + list->line_char, len);
	op = cmp_op(list->hash_table, total);
	return (op);
}
