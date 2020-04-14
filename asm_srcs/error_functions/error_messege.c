/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messege.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:58:13 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/14 23:31:06 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error_message.h"

void	error_message(t_func_list *list, int error_code, int kind, int file)
{
	const t_print var_list[12] = {
	e_main, e_check_n_sort, e_procces_line,
	e_get_name_or_comment, e_check_end_line,
	e_add_instruction_node, e_check_sort,
	e_add_to_hash, e_insert_operation, e_process_t_reg,
	e_process_t_ind, e_process_t_dir
	};

	var_list[file](list, error_code, kind);
	exit(-1);
}
