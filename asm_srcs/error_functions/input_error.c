/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:58:13 by igvan-de       #+#    #+#                */
/*   Updated: 2020/02/27 12:10:07 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	input_error(void)
{
	ft_putendl("No champion is give, please provide champion");
	exit(-1);
}

void	input_not_asm(char *str)
{
	ft_putendl(str);
	ft_putendl(" is not am assembly file");
}

void	input_bad_fd(void)
{
	ft_putendl("fd return -1 unable to open");
	exit(-1);
}

void	input_bad_asm(void)
{
	ft_putendl("This file will not generate a working .cor file");
	exit(-1);
}

void	failed_malloc(void)
{
	ft_putendl("Malloc failed");
	exit(-1);
}