/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 15:23:42 by mlokhors       #+#    #+#                */
/*   Updated: 2019/10/11 03:53:34 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "utility.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
