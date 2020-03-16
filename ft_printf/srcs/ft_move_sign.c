/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_move_sign.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 09:48:15 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 09:54:34 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_move_sign(char *str)
{
	char tmp;
	char *iter;

	while (ft_isspace(*str) == 1 && *str != '\0')
		str++;
	if (*str == '\0')
		return ;
	iter = str + 1;
	while (*iter != '\0')
	{
		if (ft_issign(*iter) == 1)
		{
			tmp = *iter;
			*iter = *str;
			*str = tmp;
		}
		iter++;
	}
}
