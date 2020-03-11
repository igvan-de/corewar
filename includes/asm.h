/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:59:43 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/11 16:35:31 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "op.h"
# include <stdbool.h>
# include <stdio.h>
# define TRUE 0
# define FALSE -1

typedef enum				s_input_variables
{
	NAME = 0,
	COMMENT = 0,
	LABEL = 0,
	STRING = 1,
	ARGUMENTS = 1,
}							t_input_variables;

typedef struct				s_count
{
	int						byte_count;
	int						i;
}							t_count;

typedef struct				s_direction
{
	unsigned char			op_code;
	char					encode;		// 1 byte //
	char 					*arg_1;
	int						arg_1_number;			// 1 byte // T_REG // 1 <-> 16 // unsigned
	char					*arg_2;
	int						arg_2_number;			//	2 bytes // T_IND of T_DIR // // signed
	char					*arg_3;
	int						arg_3_number;			//	4 bytes  // T_DIR //	 signed
	char 					*label;
	int						byte_index;
	int						byte_size;
	struct s_direction		*next;
}							t_direction;

typedef struct				s_func_list
{
	char					*name;
	char					*comment;
	int						*hash_table;
	int						line_number;
	int						line_char;
	int						byte_total;
	t_direction				*info;
}							t_func_list;

//	live
//	op_code		/	arg_1 / 	zjmp   	%label1			label1: live
// 	0			1 2 3 4 		5 		6 7 		8 				9 10 11 12

void						add_instruction_node(t_func_list *list,
							t_direction *pointer, t_count *counter);
void						get_name_or_comment(t_func_list *list, char *line);
void						process_line_into_list(t_func_list *list, char *line);
void						check_file(char *file_name, t_func_list *list);

/*
**===============================CHECK FUNCTIONS================================
*/
void						check_file(char *file_name, t_func_list *list);
void						validity_check(char *line, t_func_list *list);
void						check_name(char *line, t_func_list *list);
void						check_comment(char *line, t_func_list *list);

/*
**===============================UTILITY FUNCTIONS==============================
*/
int 						till_power(char letter, int power);
unsigned int				rev_endian(unsigned int oct);

/*
**===============================ERROR FUNCTIONS================================
*/
void						input_error(void);
void						error_message(t_func_list *list, int error_code, int kind);

/*
**===============================FREE FUNCTIONS=================================
*/
void						free_all_but_hash(t_func_list *list);
void						free_func_error(t_func_list *list);
void						free_func(t_func_list *list);
void						free_split(char **fd_name);

/*
**===============================CREATING .COR FUNCTIONS========================
*/
void						create_cor_file(char *argv, t_func_list *list);
void						write_cor_file(int fd, t_func_list *list);
void						write_champ_size(int fd, int champ_size);
void						write_champ(int fd, t_func_list *list);

#endif
