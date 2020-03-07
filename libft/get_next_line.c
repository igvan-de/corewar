/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/13 18:09:56 by igvan-de       #+#    #+#                */
/*   Updated: 2020/02/07 17:59:12 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			rearrange(t_list **node, char **line)
{
	size_t		i;
	char		*tmp;

	i = 0;
	*line = NULL;
	if (((char*)(*node)->content)[0] == '\0')
		return (0);
	while (((char*)(*node)->content)[i] != '\0' &&
		((char*)(*node)->content)[i] != '\n')
		i++;
	*line = ft_strsub((const char*)(*node)->content, 0, i);
	if (line == NULL)
		return (-1);
	if (((char*)(*node)->content)[i] == '\n')
	{
		tmp = ft_strsub((const char*)(*node)->content,
		i + 1, ft_strlen((*node)->content) - i);
		if (tmp == NULL)
			return (-1);
	}
	else
		tmp = ft_strnew(0);
	free((*node)->content);
	(*node)->content = tmp;
	return (1);
}

static t_list		*list_check(const int fd, t_list **lst)
{
	t_list *new;

	new = *lst;
	while (new)
	{
		if (new->content_size == (size_t)fd)
			return (new);
		new = new->next;
	}
	new = ft_lstnew("", 1);
	if (new == NULL)
		return (NULL);
	ft_lstadd(lst, new);
	new->content_size = (size_t)fd;
	return (new);
}

static void			create_node(char *buff, t_list *node,
					ssize_t ret)
{
	char			*tmp;

	buff[ret] = '\0';
	tmp = node->content;
	node->content = ft_strjoin(node->content, buff);
	ft_strdel(&tmp);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	ssize_t			ret;
	char			*buff;
	t_list			*node;

	ret = 1;
	if (fd < 0)
		return (-1);
	buff = (char*)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1));
	node = list_check(fd, &lst);
	if (!buff || !node || read(fd, buff, 0))
		return (-1);
	while (ret > 0 && ft_strchr(node->content, '\n') == NULL)
	{
		ret = read(fd, buff, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		create_node(buff, node, ret);
		if (node->content == NULL)
			return (-1);
	}
	free(buff);
	return (rearrange(&node, line));
}
