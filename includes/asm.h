/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:59:43 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/05/06 09:04:11 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdint.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "op.h"
# include <stdbool.h>
# include <fcntl.h>
# define S_LINE
# define ALL 7

typedef	enum				e_input_variables
{
	NAME = 0,
	COMMENT = 0,
	LABEL = 0,
	STRING = 1,
	ARGUMENTS = 1,
}							t_input_variables;

typedef struct				s_labels
{
	char					*label;
	int						index;
	struct s_labels			*next;
}							t_labels;

typedef struct				s_hash_label
{
	uint64_t				hash_label;
	t_labels				*label;
	struct s_hash_label		*next;
}							t_hash_label;

typedef struct				s_direction
{
	unsigned char			op_code;
	char					encode;
	int						*arg_num;
	char					**arg_str;
	int						byte_index;
	int						label_in_op;
	int						byte_size;
	struct s_direction		*next;
}							t_direction;

typedef struct				s_func_list
{
	char					*name;
	char					*comment;
	char					*line;
	uint64_t				*hash_table;
	int						line_number;
	int						line_char;
	int						total_bytes;
	int						new_node;
	int						cn_size;
	t_hash_label			*labels;
	t_direction				*info;
}							t_func_list;

/*
**===============================CHECK FUNCTIONS================================
*/

void						read_file(t_func_list *list, int fd);
void						get_rem_cn(t_func_list *list, int ret);
void						check_between(t_func_list *list, int err,
							int err_p, int err_f);
void						transform_label(t_func_list *list);
void						insert_encode(t_direction *new,
							int i, int operation);
void						process_t_dir(t_func_list *list, t_direction *new,
							int arg);
void						process_t_ind(t_func_list *list, t_direction *new,
							int arg);
void						process_t_reg(t_func_list *list, t_direction *new,
							int arg);
typedef	void				(*t_print)(t_func_list *list, int code, int kind);
void						add_to_hash(t_func_list *list, char *label);
void						insert_operation(t_func_list *list,
							t_direction *new);
int							calc_cmp_op(t_func_list *list, int len);
void						check_sort(t_func_list *list,
							t_direction *new, int rep);
void						add_instruction_node(t_func_list *list,
							t_direction **info,
							t_direction **pointer);
void						get_name_comment(t_func_list *list);
void						process_line(t_func_list *list);
void						check_n_process(char *file_name, t_func_list *list);
/*
**===============================UTILITY FUNCTIONS==============================
*/

void						skip_space(t_func_list *list);
void						check_end_line(t_func_list *list);
uint64_t					calc_hash(const void *bytes, size_t len);
bool						check_label_char(char c);
int							pm_atoi(t_func_list *list);
void						check_end_line(t_func_list *list);
int							till_power(char letter, int power);
unsigned int				rev_endian(unsigned int oct);
void						print_list(t_func_list *list);
void						print_bits(unsigned char octet);
bool						has_encode(unsigned char op_code);
size_t						get_tdir_size(unsigned char op_code);
int							get_bit(unsigned char octet, int index);

/*
**===============================ERROR FUNCTIONS================================
*/
void						input_error(void);
void						error_message(t_func_list *list, int error_code,
							int kind, int file);

/*
**===============================FREE FUNCTIONS=================================
*/

void						free_func(t_func_list *list);
void						free_split(char **fd_name);

/*
**===============================CREATING .COR FUNCTIONS========================
*/

typedef	void				(*t_arg)(int fd, t_direction *info, int i);
void						create_cor_file(char *argv, t_func_list *list);
void						write_cor_file(int fd, t_func_list *list);
void						write_champ_size(int fd, int champ_size);
void						write_champ(int fd, t_direction *info);
void						write_args(int fd, unsigned char new,
							t_direction *info, int i);

#endif
