/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:58:13 by igvan-de       #+#    #+#                */
/*   Updated: 2020/02/29 05:06:22 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
/*
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

*/

void	testing_only(int error_code)
{
	static char errors [9][128]={
	"not a s file in check_correct_file",
	"fd in transfer_into_struct failed",
	"error encounted in gnl in read_file",
	"error in insert_name_comment 1",
	"error in insert_name_comment 2",
	"failed in str_plit in process_line_into_list",
	"failed in validty check",
	"list->name in process_line_into_list has not been done first",
	"none of the statement in process_line_into_list is true"
	};


	ft_putendl(errors[error_code]);
}

void	free_direction(t_func_list *list)
{
	t_direction *iter;
	t_direction *next;

	iter = list->info;
	next = NULL;

	while (iter)
	{
		next = iter->next;
		if (iter->label != NULL)
			free(iter->label);
		if (iter->target_label != NULL)
			free(iter->target_label);
		iter = next;
	}
}


void	free_func(t_func_list *list)
{
	if (list->name != NULL)
	{
		free(list->name);
		list->name = NULL;
	}
	if (list->comment != NULL)
	{
		free(list->name);
		list->comment = NULL;
	}
	if (list->info != NULL)
		free_direction(list);
}

void	error_messege(t_func_list *list, int error_code, int kind)
{
	free_func(list);
	ft_putendl("Error code :");
	ft_putnbr(error_code);
//	FOR TEST USAGE ONLY DO REMOVE AFTER
	testing_only(error_code);
	if (kind == 0)
		ft_putendl("its in check_file");
	else
		ft_putendl("its in process_asm");
	ft_putendl("\n");
	exit(-1);
}