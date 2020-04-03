/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messege.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:58:13 by igvan-de       #+#    #+#                */
/*   Updated: 2020/04/03 03:43:01 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	e_process_t_dir(t_func_list *list, int error_code, int kind)
{
	static char errors [1][50]={
	"invalid input"
	};
	ft_printf("Error code : %d\n file : insert_operation\n description : %s\n",error_code, errors[kind]);
	ft_printf("at line %d", list->line_number);
	free_func(list);
}

void	e_process_t_ind(t_func_list *list, int error_code, int kind)
{
	static char errors [1][50]={
	"invalid input"
	};
	
	ft_printf("Error code : %d\n file : insert_operation\n description : %s\n",error_code, errors[kind]);
	ft_printf("at line %d char %d", list->line_number, list->line_char);
	free_func(list);
}

void	e_process_t_reg(t_func_list *list, int error_code, int kind)
{
	static char errors [3][50]={
	"invalid input",
	"bigger 16 smaller then 0",
	"invalid input"
	};
	if (error_code < 98)
		ft_printf("Error code : %d\n file : insert_operation\n description : %s\n",error_code, errors[kind]);
	else
	{
		ft_printf("Error code : %d\n file : insert_operation\n description : %s\n",error_code, errors[kind]);
		ft_printf("at line %d char : %d", list->line_number, list->line_char);
	}
	free_func(list);
}

void	e_insert_operation(t_func_list *list, int error_code, int kind)
{
	static char errors [3][50]={
	"no seperate char",
	"invalid argument with operations",
	"invalid input"
	};
	if (error_code < 86)
		ft_printf("Error code : %d\n file : insert_operation\n description : %s\n",error_code, errors[kind]);
	else
	{
		ft_printf("Error code : %d\n file : insert_operation\n description : %s\n",error_code, errors[kind]);
		ft_printf("at line %d", list->line_number);
	}
	free_func(list);
}

void	e_add_to_hash(t_func_list *list, int error_code, int kind)
{
	static char errors [1][50]={
	"malloc failed"
	};

	ft_printf("Error code : %d\n file : add_instruction_node\n description : %s\n",error_code, errors[kind]);
	free_func(list);
}


void	e_check_sort(t_func_list *list, int error_code, int kind)
{
	static char errors [3][50]={
	"label contain illegal chars",
	"ft_strsub failed",
	"invalid operation"
	};
	if (error_code < 68)
		ft_printf("Error code : %d\n file : check_sort\n description : %s\n",error_code, errors[kind]);
	else
	{
		ft_printf("Error code : %d\n file : check_sort\n description : %s\n",error_code, errors[kind]);
		ft_printf("at line %d", list->line_number);
	}
	free_func(list);
}

void	e_add_instruction_node(t_func_list *list, int error_code, int kind)
{
	static char errors [1][50]={
	"malloc failed"
	};

	ft_printf("Error code : %d\n file : add_instruction_node\n description : %s\n",error_code, errors[kind]);
	free_func(list);
}

void	e_check_end_line(t_func_list *list, int error_code, int kind)
{
	static char errors [1][50]={
	"incorrect char"
	};

	ft_printf("Error code : %d file : utility : %s\n",error_code, errors[kind]);
	ft_printf("at line %d char %d\n",list->line_number, list->line_char);
	free_func(list);
}

void	e_get_name_or_comment(t_func_list *list, int error_code, int kind)
{
	static char errors [5][50]={
	"invalid input",
	"missing \"",
	"missing second \"",
	"ft_strsub failed",
	"name/comment to big"
	};

	if (error_code < 39)
		ft_printf("Error code : %d\n file : get_name_comment\n description : %s\n",error_code, errors[kind]);
	else
	{
		ft_printf("Error code : %d\n file : get_name_comment\n description : %s\n at line %d char %d wrong character\n"
		,error_code, errors[kind], list->line_number, list->line_char);
	}
	free_func(list);
}

void	e_procces_line(t_func_list *list, int error_code, int kind)
{
	static char errors [1][50]={
	"no champion name"
	};

	ft_printf("Error code : %d\n file : process_line\n description : %s\n",error_code, errors[kind]);
	free_func(list);
}

void	e_check_n_sort(t_func_list *list, int error_code, int kind)
{
	static char errors [3][50]={
	"not a .s file",
	"fd failed",
	"gnl failed"
	};

	ft_printf("Error code : %d\n file : check_n_sort\n description : %s\n",error_code, errors[kind]);
	free_func(list);
}

void	e_main(t_func_list *list, int error_code, int kind)
{
	static char errors [2][50]={
	"no file given",
	"hash table has failed"
	};

	ft_printf("Error code : %d\n file : main\n description : %s\n",error_code ,errors[kind]);
	free_func(list);
}

void	error_message(t_func_list *list, int error_code, int kind, int file)
{
	const t_print var_list[12] = {
	e_main, e_check_n_sort, e_procces_line,
	e_get_name_or_comment, e_check_end_line, e_add_instruction_node, e_check_sort,
	e_add_to_hash, e_insert_operation, e_process_t_reg, e_process_t_ind, e_process_t_dir
	};

	var_list[file](list, error_code, kind);

	exit(-1);
}
