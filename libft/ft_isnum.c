/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isnum.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 17:43:55 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/30 17:44:36 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isnum(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
			i++;
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
