/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_message.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:58:13 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/06/05 17:37:17 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error_message.h"

/*
** @brief	display error messeges
**
** @param	list = the container where we store all our information
** @param	error_code = error code
** @param	kind = is used which part within the error needs to be printed
** @param	file = a number which represent on which file is about
*/

void	error_message(t_func_list *list, int error_code, int kind, int file)
{
	const t_print var_list[15] = {
	e_main, e_check_n_sort, e_procces_line,
	e_get_name_or_comment, e_check_end_line,
	e_add_instruction_node, e_check_sort,
	e_add_to_hash, e_insert_operation, e_process_t_reg,
	e_process_t_ind, e_process_t_dir, e_transform_arg_label,
	e_get_rem_cn, e_read_file
	};

	var_list[file](list, error_code, kind);
	exit(1);
}
