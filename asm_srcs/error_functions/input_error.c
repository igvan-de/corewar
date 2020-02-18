/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:58:13 by igvan-de       #+#    #+#                */
/*   Updated: 2020/02/17 17:09:17 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	input_error(void)
{
	ft_putendl("No champion is give, please provide champion");
	exit(-1);
}
