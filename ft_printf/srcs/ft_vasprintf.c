/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vasprintf.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/14 08:08:57 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/14 09:53:57 by jdunnink      ########   odam.nl         */
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

static	int	read_specifier(char **format, va_list a_list, char **tmp, int *sig)
{
	t_spec	*info;
	int		res;

	*sig = 1;
	res = 1;
	info = NULL;
	*format = *format + 1;
	info = pf_get_specinfo(format, info);
	res = pf_dispatch(tmp, *info, a_list);
	free(info->flags);
	free(info);
	if (res == 0)
		write(1, 0, 1);
	return (res);
}

static void	write_buf(char **buf, size_t *total, size_t *curr, int *sig)
{
	write(1, *buf, *curr);
	free(*buf);
	*buf = 0;
	*total += *curr;
	*curr = 0;
	*sig = 0;
}

static void	init_var(int *sig, size_t *total, size_t *curr, char **tmp)
{
	*sig = 0;
	*total = 0;
	*curr = 0;
	*tmp = 0;
}

int			ft_vasprintf(char **d, const char *f, va_list a, int res)
{
	char	*tmp;
	size_t	total_len;
	size_t	curr_len;
	int		sig;

	init_var(&sig, &total_len, &curr_len, &tmp);
	while (*f != '\0')
	{
		if (*f == '%')
		{
			res = read_specifier((char**)&f, a, &tmp, &sig);
			if (res == 0)
				curr_len++;
			else if (res == -1)
				return (0);
		}
		else
			tmp = ft_ctostr(*f);
		curr_len += ft_strlen(tmp);
		*d = ft_stradd(*d, tmp);
		if (curr_len >= BUFF_SIZE || *(f + 1) == '\0' || sig == 1)
			write_buf(d, &total_len, &curr_len, &sig);
		f++;
	}
	return (total_len);
}
