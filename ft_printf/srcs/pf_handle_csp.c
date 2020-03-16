/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_handle_csp.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:16:15 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/14 08:46:52 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	char	*pf_csp_width(char *arg, int width_on, int width, char *flags)
{
	char	*padding;
	char	*dest;
	int		ob_len;
	int		pad_len;

	ob_len = ft_strlen(arg);
	if (width_on == 0 || width < ob_len)
		return (arg);
	pad_len = width - ob_len;
	padding = ft_strnew_c(pad_len, ' ');
	if (!padding)
		return (arg);
	if (ft_cinstr(flags, '-') == 1)
		dest = ft_strjoin_free(arg, padding, 3);
	else
		dest = ft_strjoin_free(padding, arg, 3);
	return (dest);
}

static	char	*pf_s_precis(char *arg, int prec_on, int precision)
{
	char *dest;

	if (prec_on == 1 && precision == 0)
	{
		free(arg);
		return (ft_ctostr('\0'));
	}
	if (prec_on == 0 || precision > (int)ft_strlen(arg))
		return (arg);
	dest = ft_strndup(arg, precision);
	free(arg);
	return (dest);
}

static	void	pf_get_char(va_list a, char **arg, int *tmp_char)
{
	*tmp_char = (char)va_arg(a, int);
	*arg = ft_ctostr(*tmp_char);
}

static void		pf_get_str(t_spec info, va_list a, char **arg, char **tmp_str)
{
	*tmp_str = (char *)va_arg(a, char *);
	if (*tmp_str == NULL)
		*arg = ft_strdup("(null)");
	else
		*arg = ft_strdup(*tmp_str);
	*arg = pf_s_precis(*arg, info.prec_on, info.precis);
}

int				pf_handle_csp(char **arg, t_spec info, va_list a)
{
	char		*tmp_str;
	int			tmp_char;

	tmp_char = 1;
	if (info.type == 'c')
		pf_get_char(a, arg, &tmp_char);
	else if (info.type == 's')
		pf_get_str(info, a, arg, &tmp_str);
	else if (info.type == 'p')
		*arg = ft_strjoin_free("0x", ft_ptoa(va_arg(a, void *), 16), 2);
	else
		*arg = ft_ctostr(info.type);
	if (tmp_char == 0 && info.width_on == 1)
		info.width--;
	*arg = pf_csp_width(*arg, info.width_on, info.width, info.flags);
	if (tmp_char == 0)
		return (0);
	return (1);
}
