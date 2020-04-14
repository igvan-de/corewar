/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_p3.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 23:27:28 by mark          #+#    #+#                 */
/*   Updated: 2020/04/14 23:28:59 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	e_process_t_dir(t_func_list *list, int error_code, int kind)
{
	static char errors[1][50] = {
	"invalid input"
	};

	ft_printf("Error code:%d\nfile: process_t_dir\ndescription: %s\n",
	error_code, errors[kind]);
	ft_printf("at line %d char %d\n", list->line_number, list->line_char);
	free_func(list);
}

void	e_process_t_ind(t_func_list *list, int error_code, int kind)
{
	static char errors[1][50] = {
	"invalid input"
	};

	ft_printf("Error code:%d\nfile: process_t_ind\ndescription: %s\n",
	error_code, errors[kind]);
	ft_printf("at line %d char %d", list->line_number, list->line_char);
	free_func(list);
}
