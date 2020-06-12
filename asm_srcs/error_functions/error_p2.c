/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_p2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 23:21:48 by mark          #+#    #+#                 */
/*   Updated: 2020/06/05 17:46:07 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	e_process_t_reg(t_func_list *list, int error_code, int kind)
{
	const char errors[3][50] = {
	"invalid input",
	"T_REG > 99 or T_REG < 0",
	"invalid input"
	};

	if (error_code < 98)
	{
		ft_printf("Error code:%d\nfile:insert_operation\ndescription: %s\n",
		error_code, errors[kind]);
	}
	else
	{
		ft_printf("Error code:%d\nfile:insert_operation\ndescription: %s\n",
		error_code, errors[kind]);
		ft_printf("at line %d char : %d\n", list->line_number, list->line_char);
	}
	free_func(list);
}

void	e_insert_operation(t_func_list *list, int error_code, int kind)
{
	const char errors[3][50] = {
	"no seperate char",
	"invalid argument with operations",
	"invalid input"
	};

	if (error_code < 86)
	{
		ft_printf("Error code:%d\nfile:insert_operation\ndescription: %s\n",
		error_code, errors[kind]);
	}
	else
	{
		ft_printf("Error code:%d\nfile:insert_operation\ndescription: %s\n",
		error_code, errors[kind]);
		ft_printf("at line %d\n", list->line_number);
	}
	free_func(list);
}

void	e_add_to_hash(t_func_list *list, int error_code, int kind)
{
	const char errors[1][50] = {
	"malloc failed"
	};

	ft_printf("Error code:%d\nfile:add_instruction_node\ndescription: %s\n",
	error_code, errors[kind]);
	free_func(list);
}

void	e_check_sort(t_func_list *list, int error_code, int kind)
{
	const char errors[3][50] = {
	"label contain illegal chars",
	"ft_strsub failed",
	"invalid operation"
	};

	ft_printf("Error code:%d\nfile:check_sort\ndescription: %s\n",
	error_code, errors[kind]);
	ft_printf("at line %d\n", list->line_number);
	free_func(list);
}

void	e_add_instruction_node(t_func_list *list, int error_code, int kind)
{
	const char errors[1][50] = {
	"malloc failed"
	};

	ft_printf("Error code:%d\nfile:add_instruction_node\ndescription: %s\n",
	error_code, errors[kind]);
	free_func(list);
}
