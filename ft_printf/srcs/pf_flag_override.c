/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_flag_override.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:06:05 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 09:57:51 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	char	*remove_dup(char *str)
{
	int		i;
	char	*dest;

	if (!str)
		return (0);
	i = 0;
	dest = 0;
	while (str[i] != '\0')
	{
		if (ft_cinstr(dest, str[i]) == 0)
			dest = ft_stradd(dest, ft_ctostr(str[i]));
		else if (str[i] == 'l' && ft_count_cinstr(dest, str[i]) == 1)
			dest = ft_stradd(dest, ft_ctostr(str[i]));
		else if (str[i] == 'h' && ft_count_cinstr(dest, str[i]) == 1)
			dest = ft_stradd(dest, ft_ctostr(str[i]));
		i++;
	}
	return (dest);
}

void			pf_flag_override(t_spec *f)
{
	char *new_flags;

	if (ft_cinstr(f->flags, '-') == 1 && ft_cinstr(f->flags, '0') == 1)
	{
		new_flags = ft_strdup_exep(f->flags, '0');
		free(f->flags);
		f->flags = new_flags;
	}
	if (ft_cinstr(f->flags, ' ') == 1 && ft_cinstr(f->flags, '+') == 1)
	{
		new_flags = ft_strdup_exep(f->flags, ' ');
		free(f->flags);
		f->flags = new_flags;
	}
	if (f->flags != 0 && ft_strlen(f->flags) > 1)
	{
		new_flags = remove_dup(f->flags);
		free(f->flags);
		f->flags = new_flags;
	}
}
