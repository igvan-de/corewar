/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:58:13 by igvan-de       #+#    #+#                */
/*   Updated: 2020/02/20 13:47:52 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	input_error(void)
{
	ft_putendl("No champion is give, please provide champion");
	exit(-1);
}

void	input_not_asm(void)
{
	ft_putendl("This file is not am assembly file");
	exit(-1);
}

void	input_bad_asm(void)
{
	ft_putendl("This file will not generate a working .cor file");
	exit(-1);
}

void	failed_malloc_process(void)
{
	ft_putendl("Malloc failed in process asm function");
	exit(-1);
}