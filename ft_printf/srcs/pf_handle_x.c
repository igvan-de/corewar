/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_handle_xX.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:39:27 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 10:11:34 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	char	*add_prefix(char *arg, char type)
{
	char *prefix;
	char *dest;

	if (ft_str_only(arg, '0') == 1)
		return (arg);
	if (type == 'X')
		prefix = ft_strdup("0X");
	else
		prefix = ft_strdup("0x");
	dest = ft_strjoin_free(prefix, arg, 3);
	return (dest);
}

static	char	*pf_x_width(char *arg, int pad_size, char *flags)
{
	char	*pad;
	char	*dest;

	pad = ft_strnew_c(pad_size, ' ');
	if (ft_cinstr(flags, '-') == 1)
		dest = ft_strjoin_free(arg, pad, 3);
	else
		dest = ft_strjoin_free(pad, arg, 3);
	return (dest);
}

static	char	*pf_x_precis(char *arg, int precis)
{
	int		arg_len;
	int		pad_len;
	char	*padding;
	char	*dest;

	arg_len = ft_strlen(arg);
	if (precis <= arg_len)
		return (arg);
	pad_len = precis - arg_len;
	padding = ft_strnew_c(pad_len, '0');
	dest = ft_strjoin_free(padding, arg, 3);
	return (dest);
}

static	void	format_x(t_spec info, char **tmp, unsigned long long res)
{
	char				*new_tmp;

	if (info.prec_on == 1)
		*tmp = pf_x_precis(*tmp, info.precis);
	if (info.prec_on == 1 && info.precis == 0 && **tmp == '0')
	{
		new_tmp = ft_strdup_exep(*tmp, '0');
		free(*tmp);
		*tmp = new_tmp;
	}
	else if (info.width_on == 1 && ft_cinstr(info.flags, '0') == 1 &&
			info.prec_on == 0)
	{
		if (ft_cinstr(info.flags, '#') == 1 && ft_str_only(*tmp, '0') == 0)
			*tmp = pf_x_precis(*tmp, info.width - 2);
		else
			*tmp = pf_x_precis(*tmp, info.width);
	}
	if (ft_cinstr(info.flags, '#') == 1 && res != 0)
		*tmp = add_prefix(*tmp, info.type);
	if (info.width_on == 1 && info.width > (int)ft_strlen(*tmp))
		*tmp = pf_x_width(*tmp, info.width - ft_strlen(*tmp), info.flags);
}

int				pf_handle_x(char **tmp, t_spec info, va_list a_list)
{
	unsigned long long	res;

	res = (unsigned long long)va_arg(a_list, unsigned long long);
	if (res == 0)
		*tmp = ft_ctostr('0');
	else if (info.type == 'x')
		*tmp = pf_toa_unsign(res, 16, info.type_size, 1);
	else if (info.type == 'X')
		*tmp = pf_toa_unsign(res, 16, info.type_size, 2);
	format_x(info, tmp, res);
	return (1);
}
