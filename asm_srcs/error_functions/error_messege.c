/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messege.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:58:13 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/06 14:10:17 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*error_function(int error_code)
{
	static char errors [15][128]={
	"init_func_list",
	"no files are given",
	"check_correct_file",
	"transfer_into_struct",
	"found_str malloc failed",
	"comment length or program length exceeded the max",
	"add_instruction first iteration",
	"add_instruction x iteration",
	"get_label_name -> ft_strsub failed",
	"",
	"malloc contineu node failed in add_instruction_node",
	"error in get_op_code",
	"error in make_hash_table",
	"error in get_op_code",
	"error in main.c no arguments"
	};

}

void	error_messege(t_func_list *list, int error_code, int kind)
{
	static char loc[5][25] = {
	"its in init_func_list, ",
	"its in main, "
	"its in check file, ",
	"its in process_asm, ",
	""
	};

	if (error_code < 100)
		ft_printf("Error code %d, %s in function: %s\n", error_code, loc[kind], error_function(error_code));
	else if (error_code == 100)
		ft_printf("Lexical error at [%d:%d]\n", list->line_number, list->line_char);
	else if (error_code == 101)
		ft_printf("Invalid instruction [%.3d:%.3d]\n", list->line_number, list->line_char);
	else if (error_code == 102)
		ft_printf("Syntax error at [%.3d:%.3d]\n", list->line_number, list->line_char);
	free_func(list);
	exit(-1);
}