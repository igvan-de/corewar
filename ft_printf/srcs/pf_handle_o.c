/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_handle_o.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/06 13:48:26 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/06 13:50:24 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	char	*pf_o_width(char *arg, int pad_size, t_spec info)
{
	char	*pad;
	char	*dest;
	char	c;

	c = ' ';
	if (ft_cinstr(info.flags, '0') == 1 && info.prec_on == 0)
		c = '0';
	pad = ft_strnew_c(pad_size, c);
	if (ft_cinstr(info.flags, '-') == 1)
		dest = ft_strjoin_free(arg, pad, 3);
	else
		dest = ft_strjoin_free(pad, arg, 3);
	return (dest);
}

static	char	*pf_o_precis(char *arg, int pad_size, char c)
{
	char	*pad;
	char	*dest;

	pad = ft_strnew_c(pad_size, c);
	dest = ft_strjoin_free(pad, arg, 3);
	return (dest);
}

static size_t	count_digits(char *str)
{
	size_t count;

	count = 0;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			count++;
		str++;
	}
	return (count);
}

int				pf_handle_o(char **tmp, t_spec info, va_list a_list)
{
	unsigned long long	res;
	int					check;

	res = (unsigned long long)va_arg(a_list, unsigned long long);
	if (res == 0 && info.prec_on == 1 && info.precis == 0)
		*tmp = ft_ctostr('\0');
	else if (res == 0)
		*tmp = ft_ctostr('0');
	else
		*tmp = pf_toa_unsign(res, 8, info.type_size, 1);
	if (ft_cinstr(info.flags, '#') == 1 && **tmp != '0')
		*tmp = ft_strjoin_free("0", *tmp, 2);
	check = count_digits(*tmp);
	if (info.prec_on == 1 && info.precis > check)
		*tmp = pf_o_precis(*tmp, info.precis - check, '0');
	check = ft_strlen(*tmp);
	if (info.width_on == 1 && info.width > check)
		*tmp = pf_o_width(*tmp, info.width - check, info);
	return (1);
}
