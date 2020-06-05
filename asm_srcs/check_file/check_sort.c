/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 01:01:53 by mark          #+#    #+#                 */
/*   Updated: 2020/06/05 17:54:29 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief	checks if there en encode byte.
**
** @param 	op_code = number of the operation
** @return 	int = the op-code and encode byte in byte size
**			if there no encode byte in return size of op_code
*/

static int		if_encode(int op_code)
{
	const int	encode[16] = {1, 2, 2, 2, 2, 2, 2, 2, 1,
	2, 2, 1, 2, 2, 1, 2};

	return (encode[op_code - 1]);
}

/*
** @brief	checks if the operation is valid
**
** @param	list = the container where we store all our information
** @param	list->line_char = keep track the index accesed in line.
** @param	list->total_bytes = keeps track of the amount of bytes
** @param	new = memory adress from a new or existing list.
**			it always has the last node in the list
**			this list contains all the information for a operation
** @param	new->opcode = assign operation code
** @param	i = length of possible operation
**
** check if its an valid op_code.
** Also it checks if there is an encode byte
** it will add to the total bytes and to the node byte amount
*/

static void		check_operation(t_func_list *list,
		t_direction *new, int i)
{
	int number;
	int len;
	int op_encode;

	op_encode = 0;
	number = 0;
	len = i - list->line_char;
	if (list->line[i] == COMMENT_CHAR)
	{
		list->line_char = i;
		return ;
	}
	if (len > 5 || len <= 0)
		error_message(list, 69, 2, 6);
	number = calc_cmp_op(list, len);
	if (number == -1)
		error_message(list, 68, 2, 6);
	new->op_code = number;
	op_encode = if_encode(number);
	list->total_bytes += op_encode;
	new->byte_size += op_encode;
	list->line_char = i;
}

/*
** @brief	checks if there is a label name and process it
**
** @param	list = the container where we store all our information
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
** @param	len = the label length
**
** checks the label with correct chars then it makes a sub string.
** after the substring has been made it will convert to a hash
** it will be added into a new list that remembers the hash.
** and the index. so once everything is finished it can easily
** convert labels to the indirect value based on the index
*/

static void		get_label_name(t_func_list *list,
				int len)
{
	int		start;
	int		ret;
	char	*sub;

	sub = NULL;
	start = list->line_char;
	ret = 0;
	while (list->line_char < len - 1)
	{
		ret = check_label_char(list->line[list->line_char]);
		if (ret == false)
			error_message(list, 60, 0, 6);
		list->line_char++;
	}
	sub = ft_strsub(list->line, start, list->line_char - start);
	if (sub == NULL)
		error_message(list, 61, 1, 6);
	add_to_hash(list, sub);
	free(sub);
	list->line_char = len;
}

/*
** @brief	check for name or comment then process rest
**
** @param	list = the container where we store all our information
** @param	list->line = it readed line by line from the file and assign to line
** @param	list->line_char = keep track the index accesed in line.
** @param	new = memory adress from a new or existing list.
**			it always has the last node in the list
**			this list contains all the information for a operation
** @param	rep = repeat so its a safety. to prvent from infinite loop.
**
** this is quite a heavy read. so it first check for a label name
** if this has been found it will process then it will recurse so it
** will check again. because its already been found it will skip this
** and goes straight to the process the remaining arguments.
** or it stops since the the end of line have been found.
** it wil set list->new_node to 1 so no new node is being made
*/

void			check_sort(t_func_list *list,
		t_direction *new, int rep)
{
	int i;

	i = 0;
	skip_space(list);
	i = list->line_char;
	while (list->line[i] && ft_isspace(list->line[i]) == 0 &&
		list->line[i] != DIRECT_CHAR && list->line[i] != '-' &&
		list->line[i] != COMMENT_CHAR && list->line[i] != LABEL_CHAR)
		i++;
	if (list->line[i] == LABEL_CHAR && rep == 0)
	{
		get_label_name(list, i + 1);
		list->line_char = i + 1;
		skip_space(list);
		if (list->line[list->line_char] == '\0')
		{
			list->new_node = 1;
			return ;
		}
		else
			return (check_sort(list, new, 1));
	}
	else
		check_operation(list, new, i);
}
