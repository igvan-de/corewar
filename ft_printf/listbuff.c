/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   listbuff.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/21 20:30:38 by mark           #+#    #+#                */
/*   Updated: 2019/10/11 03:42:04 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./utility/utility.h"
#include <unistd.h>

void		empty(t_container *list)
{
	list->lengthmod = 0;
	list->flags = 0;
	list->precision = -1;
	list->width = -1;
	list->bit = 0;
}

void		addbuff(t_container *list, char c)
{
	list->buff[list->i] = c;
	list->i++;
	if (list->i == BUFF_SIZE)
		list->writer(list);
}

void		writer_fd(t_container *list)
{
	list->total += list->i;
	write(list->fd, list->buff, list->i);
	ft_memset(list->buff, 0, BUFF_SIZE);
	list->i = 0;
}

void		writer_str(t_container *list)
{
	char *tmp;

	tmp = NULL;
	if (list->total == 0)
		list->str = (void *)ft_strdup(list->buff);
	else
	{
		tmp = ft_strjoin((char *)list->str, list->buff);
		free(list->str);
		list->str = tmp;
	}
}
