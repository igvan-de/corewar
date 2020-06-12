/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_p1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 23:13:55 by mark          #+#    #+#                 */
/*   Updated: 2020/06/05 17:36:48 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	e_check_end_line(t_func_list *list, int error_code, int kind)
{
	const char errors[1][50] = {
	"incorrect char"
	};

	ft_printf("Error code:%d\nfile:utility\ndescription: %s\n",
	error_code, errors[kind]);
	ft_printf("at line %d char %d\n", list->line_number, list->line_char);
	free_func(list);
}

void	e_get_name_or_comment(t_func_list *list, int error_code, int kind)
{
	const char errors[7][50] = {
	"invalid input",
	"missing \"",
	"missing second \"",
	"ft_strsub failed",
	"name/comment to big",
	"name already initialised",
	"comment already initialised"
	};

	if (error_code < 38)
		ft_printf("Error code:%d\nfile:get_name_comment\ndescription: %s\n",
		error_code, errors[kind]);
	else
	{
		ft_printf("Error code:%d\n", error_code);
		ft_printf("file:get_name_comment\ndescription: %s\n", errors[kind]);
		ft_printf("at line %d char %d\n",
		list->line_number, list->line_char);
	}
	free_func(list);
}

void	e_procces_line(t_func_list *list, int error_code, int kind)
{
	const char errors[1][50] = {
	"no champion name or no comment"
	};

	ft_printf("Error code:%d\nfile:process_line\ndescription: %s\n",
	error_code, errors[kind]);
	free_func(list);
}

void	e_check_n_sort(t_func_list *list, int error_code, int kind)
{
	const char errors[3][50] = {
	"not a .s file",
	"fd failed",
	"empty file"
	};

	ft_printf("Error code:%d\nfile:check_n_sort\ndescription: %s\n",
	error_code, errors[kind]);
	free_func(list);
}

void	e_main(t_func_list *list, int error_code, int kind)
{
	const char errors[3][50] = {
	"no file given",
	"hash table has failed",
	"no instuction given"
	};

	ft_printf("Error code:%d\nfile:main\ndescription: %s\n",
	error_code, errors[kind]);
	free_func(list);
}
