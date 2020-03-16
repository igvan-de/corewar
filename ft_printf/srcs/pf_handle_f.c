/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_handle_fF.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:19:35 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 10:04:31 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	char	*pf_f_width(char *arg, int pad_size, char *flags, char c)
{
	char	*pad;
	char	*dest;

	pad = ft_strnew_c(pad_size, c);
	if (ft_cinstr(flags, '-') == 1)
		dest = ft_strjoin_free(arg, pad, 3);
	else
		dest = ft_strjoin_free(pad, arg, 3);
	return (dest);
}

static	char	*add_dot(char *arg)
{
	char	*ptr;

	ptr = arg;
	while (ft_cinstr("-+0123456789", *ptr) == 1)
		ptr++;
	if (*ptr == '\0')
	{
		ptr = ft_strjoin_free(arg, ".", 1);
		return (ptr);
	}
	if (*ptr == ' ')
	{
		*ptr = '.';
		return (arg);
	}
	return (arg);
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

static	void	format_f(t_spec info, char **tmp)
{
	char *new_tmp;

	if (info.prec_on == 1 && info.precis == 0)
	{
		new_tmp = ft_strdup_until(*tmp, '.');
		free(*tmp);
		*tmp = new_tmp;
	}
	if (ft_cinstr(info.flags, '+') && **tmp != '-')
		*tmp = ft_strjoin_free("+", *tmp, 2);
	if (ft_cinstr(*tmp, '.') == 0 && ft_cinstr(info.flags, '#') == 1)
		*tmp = add_dot(*tmp);
	if (ft_cinstr(info.flags, ' ') == 1 && ft_cinstr(*tmp, '-') == 0 &&
		ft_cinstr(*tmp, '+') == 0)
		*tmp = ft_strjoin_free(" ", *tmp, 2);
	if (info.width_on == 1 && (int)ft_strlen(*tmp) < info.width &&
		ft_cinstr(info.flags, '0') == 1)
		*tmp = pf_f_width(*tmp, info.width - ft_strlen(*tmp), info.flags, '0');
	else if (info.width_on == 1 && (int)ft_strlen(*tmp) < info.width &&
			ft_cinstr(info.flags, '0') == 0)
		*tmp = pf_f_width(*tmp, info.width - ft_strlen(*tmp), info.flags, ' ');
	move_space(*tmp);
	ft_move_sign(*tmp);
}

int				pf_handle_f(char **tmp, t_spec info, va_list a_list)
{
	if (info.precis == 0 && info.prec_on == 1)
		info.precis = 0;
	else if (info.precis == 0 && info.prec_on == 0)
		info.precis = 6;
	if (info.type_size == 2)
		*tmp = pf_dtoa(va_arg(a_list, long double), info.precis);
	else
		*tmp = pf_dtoa(va_arg(a_list, double), info.precis);
	format_f(info, tmp);
	return (1);
}
