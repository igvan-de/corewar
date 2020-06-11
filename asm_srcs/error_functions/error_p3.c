/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_p3.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 23:27:28 by mark          #+#    #+#                 */
/*   Updated: 2020/06/11 16:04:38 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	e_read_file(t_func_list *list, int error_code, int kind)
{
	const char errors[3][50] = {
	"fail read in gnl",
	"no new line end of file"
	};

	if (error_code == 142)
		ft_printf("no closing \" has been found\n");
	else
		ft_printf("Error code:%d\nfile: e_read_file\ndescription: %s\n",
	error_code, errors[kind]);
	free_func(list);
}

void	e_get_rem_cn(t_func_list *list, int error_code, int kind)
{
	const char errors[2][50] = {
	"malloc failed",
	"name or comment to big or no \""
	};

	ft_printf("Error code:%d\nfile: get_rem_cn\ndescription: %s\n",
	error_code, errors[kind]);
	free_func(list);
}

void	e_transform_arg_label(t_func_list *list, int error_code, int kind)
{
	const char errors[2][50] = {
	"label hash doesnt exist",
	"label hash exist. label name not found"
	};

	ft_printf("Error code:%d\nfile: transform_arg_label\ndescription: %s\n",
	error_code, errors[kind]);
	free_func(list);
}

void	e_process_t_dir(t_func_list *list, int error_code, int kind)
{
	const char errors[1][50] = {
	"invalid input"
	};

	ft_printf("Error code:%d\nfile: process_t_dir\ndescription: %s\n",
	error_code, errors[kind]);
	ft_printf("at line %d char %d\n", list->line_number, list->line_char);
	free_func(list);
}

void	e_process_t_ind(t_func_list *list, int error_code, int kind)
{
	const char errors[1][50] = {
	"invalid input"
	};

	ft_printf("Error code:%d\nfile: process_t_ind\ndescription: %s\n",
	error_code, errors[kind]);
	ft_printf("at line %d char %d\n", list->line_number, list->line_char);
	free_func(list);
}
