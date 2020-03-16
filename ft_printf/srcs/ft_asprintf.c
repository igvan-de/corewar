/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/27 07:38:44 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 09:49:48 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	int	pf_dispatch(char **tmp, t_spec info, va_list a_list)
{
	if (ft_cinstr("%csp", info.type) == 1)
		return (pf_handle_csp(tmp, info, a_list));
	else if (ft_cinstr("iduU", info.type) == 1)
		return (pf_handle_idu(tmp, info, a_list));
	else if (ft_cinstr("xX", info.type) == 1)
		return (pf_handle_x(tmp, info, a_list));
	else if (info.type == 'f')
		return (pf_handle_f(tmp, info, a_list));
	else if (info.type == 'o')
		return (pf_handle_o(tmp, info, a_list));
	return (-1);
}

static	int	read_specifier(char **format, va_list a_list, char **tmp)
{
	t_spec	*info;
	int		res;

	info = NULL;
	*format = *format + 1;
	info = pf_get_specinfo(format, info);
	res = pf_dispatch(tmp, *info, a_list);
	free(info->flags);
	free(info);
	if (res == -1)
		return (-1);
	return (0);
}

int			ft_asprintf(char **dest, const char *format, ...)
{
	va_list	a_list;
	char	*tmp;
	size_t	total_len;

	*dest = 0;
	total_len = 0;
	tmp = 0;
	va_start(a_list, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (read_specifier((char**)&format, a_list, &tmp) == -1)
				return (0);
		}
		else
			tmp = ft_ctostr(*format);
		total_len += ft_strlen(tmp);
		*dest = ft_stradd(*dest, tmp);
		format++;
	}
	va_end(a_list);
	return (total_len);
}
