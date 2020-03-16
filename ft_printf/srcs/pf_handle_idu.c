/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_handle_idu.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:29:31 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 10:02:53 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	char	*pf_idu_precis(char *arg, int pad_size, char c)
{
	char	*pad;
	char	*dest;

	pad = ft_strnew_c(pad_size, c);
	dest = ft_strjoin_free(pad, arg, 3);
	return (dest);
}

static	char	*pf_idu_width(char *arg, int pad_size, t_spec info)
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

static void		move_space(char *str)
{
	int		digits;
	char	tmp;
	char	*swap;

	swap = str;
	digits = ft_count_digits(str);
	if (*str == ' ')
		return ;
	while (*str != '\0' && digits > 0)
	{
		if (*str == ' ')
		{
			tmp = *str;
			*str = *swap;
			*swap = tmp;
		}
		str++;
		digits--;
	}
}

static void		format_int(t_spec info, char **tmp)
{
	int res;

	if (ft_cinstr(info.flags, '+') == 1 && **tmp != '-' && info.type != 'u')
		*tmp = ft_strjoin_free("+", *tmp, 2);
	res = ft_count_digits(*tmp);
	if (info.prec_on == 1 && info.precis > res)
		*tmp = pf_idu_precis(*tmp, info.precis - res, '0');
	if (ft_cinstr(info.flags, ' ') &&
		ft_cinstr(*tmp, '-') == 0 && info.type != 'u')
		*tmp = ft_strjoin_free(" ", *tmp, 2);
	res = ft_strlen(*tmp);
	if (info.width_on == 1 && info.width > res)
		*tmp = pf_idu_width(*tmp, info.width - res, info);
	ft_move_sign(*tmp);
	if (ft_cinstr(info.flags, ' ') == 1)
		move_space(*tmp);
}

int				pf_handle_idu(char **tmp, t_spec i, va_list a)
{
	if (ft_cinstr("id", i.type) == 1)
		*tmp = pf_toa_sign(va_arg(a, long long), 10, i.type_size, 1);
	else if (i.type == 'u' || i.type == 'U')
		*tmp = pf_toa_unsign(va_arg(a, unsigned long long), 10, i.type_size, 1);
	if (i.prec_on == 1 && i.precis == 0 && **tmp == '0')
	{
		free(*tmp);
		*tmp = ft_ctostr('\0');
	}
	format_int(i, tmp);
	return (1);
}
