/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_message.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 23:08:36 by mark          #+#    #+#                 */
/*   Updated: 2020/04/15 03:06:50 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGE_H
# define ERROR_MESSAGE_H
# include "asm.h"

void		e_main(t_func_list *list, int error_code, int kind);
void		e_check_n_sort(t_func_list *list, int error_code, int kind);
void		e_procces_line(t_func_list *list, int error_code, int kind);
void		e_get_name_or_comment(t_func_list *list, int error_code, int kind);
void		e_check_end_line(t_func_list *list, int error_code, int kind);
void		e_add_instruction_node(t_func_list *list, int error_code, int kind);
void		e_check_sort(t_func_list *list, int error_code, int kind);
void		e_add_to_hash(t_func_list *list, int error_code, int kind);
void		e_insert_operation(t_func_list *list, int error_code, int kind);
void		e_process_t_reg(t_func_list *list, int error_code, int kind);
void		e_process_t_ind(t_func_list *list, int error_code, int kind);
void		e_process_t_dir(t_func_list *list, int error_code, int kind);
void		e_transform_arg_label(t_func_list *list, int error_code, int kind);

#endif