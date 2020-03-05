/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:58:13 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/05 13:03:39 by igvan-de      ########   odam.nl         */
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
	static char errors [14][128]={
	"not a s file in check_correct_file",
	"fd in transfer_into_struct failed",
	"error encounted in gnl in read_file",
	"error in insert_name_comment 1",
	"error in insert_name_comment 2",
	"failed in str_plit in process_line_into_list",
	"failed in validty check",
	"list->name in process_line_into_list has not been done first",
	"none of the statement in process_line_into_list is true",
	"malloc start node failed in add_instruction_node",
	"malloc contineu node failed in add_instruction_node",
	"error in get_op_code",
	"error in make_hash_table",
	"error in get_op_code"
	};


	ft_putendl(errors[error_code]);
}

void	error_message(t_func_list *list, int error_code, int kind)
{
	static char loc[3][25] = {
	"its in check file",
	"its in process_asm",
	"its in init_func_list",
	"its not a .s file",
	"something went wrong when opening the file, fd error"};

	free_func_error(list);
	ft_putendl("Error code :");
	ft_putnbr(error_code);
	ft_putendl("\n");
//	FOR TEST USAGE ONLY DO REMOVE AFTER
	testing_only(error_code);
	ft_putendl(loc[kind]);
	ft_putendl("\n");
}
