/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 15:46:14 by igvan-de       #+#    #+#                */
/*   Updated: 2020/02/27 13:09:36 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
// 1 file of meerdere
/*

char	*ft_strndup(const char *s1, int leng)
{
	int		i;
	int		length;
	char	*dest;

	i = 0;
	while (s1[i])
		i++;
	if (i > length)
		i = length;
	dest = (char*)ft_memalloc(sizeof(char) * i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && i < leng)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_func_list	*add_func_node()
{
	t_func_list *new;

	new = (t_func_list *)malloc(sizeof(t_func_list));
	if (!new)
		return (NULL);
	new->n = NULL;
	new->func_name = NULL;
	new->next = NULL;
}

char	*trim_name(char *file_name)
{
	int length;

	length = ft_strlen(file_name);
	length -= 2;
	return(ft_strndup(file_name, length));
}

void	process_asm(char *file_name)
{
	int		fd;
	char	*cor_name;
	int 	len;
	
	cor_name = ft_strjoin(trim_name(file_name), ".cor");
	if (cor_name == NULL)
		failed_malloc_process();
	fd = open(cor_name, O_WRONLY | O_CREAT | O_TRUNC, 644);
}
*/

void	empty_new_direction(t_direction **iter)
{
	(*iter)->op_code = 0;
	(*iter)->encode = 0;
	(*iter)->arg_1 = -1;
	(*iter)->arg_2 = -1;
	(*iter)->arg_3 = -1;
	(*iter)->has_label = 0;
	(*iter)->label = NULL;
	(*iter)->target_label = NULL;
	(*iter)->byte_index = 0;
	(*iter)->byte_size = -1;
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

int		add_and_insert_func(t_func_list *list, char *line, char *label)
{
	t_direction *iter;
	int			i;

	i = 0;
	iter = NULL;
	if (add_instruction_node(list) == -1)
		return (-1);
	iter = list->info;
	while (iter && iter->next)
	{
		iter = iter->next;
		i++;
	}
	iter->label = ft_strdup(label);
	iter->byte_index = i;
	iter->has_label = 1;
	parse_line(&iter, line)
}

int		ft_strnnchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
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
			return (-1);
	}
	else
	{
		list->comment = ft_strsub(line, start, end - start - 1);
		if (list->comment == NULL)
			return (-1);
	}
}

int		process_line_into_list(t_func_list *list, char *line, char **label)
{
	char **split;

	split = ft_strplit(line);
//	vality check here please	
//	if (validity_check_line == -1)
//		return (unvalid_line(list));
	if (ft_strcmp(split[0], ".name"))
		return (insert_name_comment(list, line, split[0]));
	else if (ft_strcmp(split[0], ".comment"))
		return (insert_comment_comment(list, line, split[0], 1));
	else if (split[0][ft_strlen(split[0])] == ':')
	{
		if (list->name != NULL)
		{
			// misschien nog een free voor label
			*label = ft_strdup(split[0]);
			if (!*label)
				return (-1);
			return (add_and_insert_func(&list, line, split[0]));
		}
		else
			return (-1);
	}
	else if (*label != NULL)
		return (insert_to_ex_func(&list, line, label));
}

int		transfer_into_struct(char *file_name, t_func_list *list)
{
	int			fd;
	int			ret;
	char		*line;
	char		last_label;

	last_label = NULL;
	line = NULL;
	ret = 1;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		input_bad_fd();
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (line != NULL && line[0] != '\0')
		{
			if (process_line_into_list(list, line, &last_label) == -1)
				return (-1);
		}
		free(line);
		line = NULL;
	}
	close(fd);
}

int		check_correct_file(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	if (file_name[len - 1] == '.' && file_name[len] == 's')
		return (0);
	return (-1);
}

void	check_file(char *file_name, t_func_list *list)
{
	if (check_correct_file(file_name) == -1)
		return (input_not_asm(file_name));
	if (transfer_into_struct(file_name, list) == -1)
		transfer_error(file_name, list);
}

int		main(int argc, char **argv)
{
	int			i;
	t_func_list list;

	list.name = NULL;
	list.comment = NULL;
	list.info = NULL;
	i = 1;
	if (argc == 0)
		input_error();
	while (argv[i])
	{
		check_file(argv[i], &list);
//		process_asm(argv[i]);
		i++;
	}
	return (0);
}
