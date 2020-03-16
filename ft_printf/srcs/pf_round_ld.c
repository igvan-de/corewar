/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_round_ld.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/14 08:56:03 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/14 08:56:21 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	void	round_string(char *ptr, size_t len, int *sig)
{
	if (len == 0 || *ptr == '-')
	{
		*sig = 3;
		return ;
	}
	if (*ptr >= '0' && *ptr < '9')
	{
		*ptr = (*ptr) + 1;
		return ;
	}
	else
	{
		if (*ptr != '.' && *ptr != '-')
			*ptr = '0';
		round_string(ptr - 1, len - 1, sig);
	}
	return ;
}

static void		add_round_digit(char **str)
{
	char *tmp;

	tmp = *str;
	if (**str != '-')
		*str = ft_strjoin_free("1", *str, 2);
	else
	{
		tmp = ft_strdup(tmp + 1);
		free(*str);
		*str = ft_strjoin_free("-1", tmp, 2);
	}
}

void			pf_round_ld(long double value, char **dest)
{
	int		res;
	char	*tmp;

	tmp = ft_str_tail(*dest);
	if (ft_isdigit(*tmp) == 0)
		tmp--;
	res = 0;
	if (value > 0.5 || (value == 0.5 && ft_cinstr("13579", *tmp) == 1))
	{
		round_string(tmp, ft_strlen(*dest), &res);
		if (res == 3)
			add_round_digit(dest);
	}
}
