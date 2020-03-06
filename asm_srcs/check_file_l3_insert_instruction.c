/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l3_insert_instruction.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 05:51:42 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/06 11:08:48 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					get_operation(int power, int *table)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (power == table[i])
			return (i);
	}
	return (-1);
}

int		get_op_code(char *operation, int *hash_table)
{
	int i;
	int max;
	int power;

	i = 0;
	power = 0;
	max = ft_strlen(operation) - 1;
	if (max > 4)
		return (12);
	while (i < max)
	{
		power += till_power(operation[i], i);
		i++;
	}
	return (get_operation(power, hash_table));
}

int		fill_in_node(t_func_list *list, t_direction *new, char **line_split, t_count *counter)
{
	int op_code;

	op_code = get_op_code(line_split[counter->i], list->hash_table);
	if (op_code == -1)
		return (14);
	if (!new)
		return (-1);
	return (0);
}



int		insert_instruction(t_func_list *list, char **line_split, int label)
{
	int ret;
	t_count counter;
	t_direction *new;

	counter.byte_count = 0;
	counter.i = 0;
	new = NULL;
	ret = add_instruction_node(list, new, &counter);
	if (ret != 0)
		return (ret);
	if (label == 1)
	{
		new->label = ft_strdup(line_split[counter.i]);
		counter.i++;
	}
	ret = fill_in_node(list, new, line_split, &counter);
	if (ret != 0)
		return (ret);
	return (0);
}