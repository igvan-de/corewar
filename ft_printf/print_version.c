/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_version.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/25 20:25:48 by mlokhors       #+#    #+#                */
/*   Updated: 2019/09/29 08:42:51 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(char *format, ...)
{
	t_container	list;
	int			ret;

	list.i = 0;
	list.total = 0;
	list.fd = 1;
	list.writer = &writer_fd;
	va_start(list.ap, format);
	ret = make_print(&list, format);
	va_end(list.ap);
	return (ret);
}

int		ft_dprintf(int fd, char *format, ...)
{
	t_container	list;
	int			ret;

	list.i = 0;
	list.total = 0;
	list.fd = fd;
	list.writer = &writer_fd;
	va_start(list.ap, format);
	ret = make_print(&list, format);
	va_end(list.ap);
	return (ret);
}

int		ft_sprintf(char *str, char *format, ...)
{
	t_container	list;
	int			ret;

	list.i = 0;
	list.total = 0;
	list.fd = 0;
	list.writer = &writer_str;
	va_start(list.ap, format);
	ret = make_print(&list, format);
	str = ft_strcpy(str, list.str);
	free(list.str);
	va_end(list.ap);
	return (ret);
}
