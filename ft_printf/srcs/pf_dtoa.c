/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/27 07:38:44 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/14 08:44:39 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	char	*get_part_one(long double value)
{
	unsigned long long	tmp;
	char				*dest;

	if (value < 1 && value > -1)
		tmp = 0;
	else
		tmp = (unsigned long long)value;
	dest = pf_toa_unsign(tmp, 10, 2, 1);
	return (dest);
}

static	void	get_part_two(long double *second, int precision, char **dest)
{
	char		new_digit;
	long double	value;

	value = *second;
	while (precision > 0)
	{
		value = value * 10;
		if (value != value)
			value = 0;
		new_digit = '0' + (int)value;
		*dest = ft_strjoin_free(*dest, ft_ctostr(new_digit), 3);
		while (value >= 1)
			value = value - 1;
		precision--;
	}
	*second = value;
}

char			*pf_dtoa(long double value, int precision)
{
	int			sign;
	char		*dest;
	long double	second;

	sign = 0;
	dest = 0;
	if (value < 0)
	{
		sign = 1;
		value = value * -1;
	}
	second = value - (unsigned long long int)value;
	dest = get_part_one(value);
	if (dest == 0)
		dest = ft_strdup("0");
	dest = ft_strjoin_free(dest, ".", 1);
	get_part_two(&second, precision, &dest);
	pf_round_ld(second, &dest);
	if (sign == 1)
		dest = ft_strjoin_free("-", dest, 2);
	return (dest);
}
