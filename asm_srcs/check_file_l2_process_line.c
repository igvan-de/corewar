/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file_l2_process_line.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 05:22:10 by mlokhors       #+#    #+#                */
/*   Updated: 2020/02/29 05:38:41 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	empty_new_direction(t_direction **iter)
{
	(*iter)->op_code = 0;
	(*iter)->encode = 0;
	(*iter)->arg_1 = 0;
	(*iter)->arg_2 = 0;
	(*iter)->arg_3 = 0;
	(*iter)->has_label = 0;
	(*iter)->label = NULL;
	(*iter)->target_label = NULL;
	(*iter)->byte_index = 0;
	(*iter)->byte_size = 0;
	(*iter)->next = NULL;
}

int		add_instruction_node(t_func_list *list)
{
	t_direction *iter;

	iter = list->info;
	if (iter == NULL)
	{
		iter = (t_direction *)malloc(sizeof(t_direction));
		if (!iter)
			return (-1);
	}
	else
	{
		while (iter)
			iter = iter->next;
		iter = (t_direction *)malloc(sizeof(t_direction));
		if (!iter)
			return (-1);
	}
	empty_new_direction(&iter);
}

int		insert_name_comment(t_func_list *list, char *line, char *name, int sort)
{
	char	*start_line;
	int		start;
	int		end;

	end = 0;
	start_line = line;
	start = ft_strnnchr(line, '\"');
	start_line += start + 1;
	end = ft_strnnchr(start_line, '\"');
	if (sort == 0)
	{
		list->name = ft_strsub(line, start, end - start - 1);
		if (list->name == NULL)
			return (4);
	}
	else
	{
		list->comment = ft_strsub(line, start, end - start - 1);
		if (list->comment == NULL)
			return (5);
	}
	return (0);
}

/*
** this will decide if its name, comment, or an instruction
*/

int		process_line(t_func_list *list, char *line, char **line_split)
{
//	vality check here please	
//	if (validity_check_line == -1)
//		return (7);
	if (ft_strcmp(line_split[0], ".name"))
		return (insert_name_comment(list, line, line_split[0], 0));
	else if (ft_strcmp(line_split[0], ".comment"))
		return (insert_name_comment(list, line, line_split[0], 1));
	else
	{
		if (list->name != NULL)
		{
			if (line_split[0][ft_strlen(line_split[0])] == ':')
				return(insert_with_label(list, line_split));
			else
				return(insert_without_label(list, line_split));
		}
		else
			return (8);
	}
	return (9);
}

void	free_split(char **split)
{
	char *line;

	line = NULL;
	while (**split)
	{
		line = *split;
		*split += 1;
		free(line);
	}
}

/*
**	because it can contain as many spaces we split it up in a double array
**	ft_strplit need to be worked on to split it on a , aswell but only one
**	,, is error
*/

int		process_line_into_list(t_func_list *list, char *line)
{
	char	**split_line;
	int		ret;

	ret = 0;
	split_line = ft_strplit(line);
	if (split_line == NULL)
		return (6);
	ret = process_line(list, line, split_line);
	if (ret != 0)
	{
		free_split(split_line);
		return (ret);
	}
	return (0);
}