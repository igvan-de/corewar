/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 16:59:43 by igvan-de       #+#    #+#                */
/*   Updated: 2020/02/27 12:28:23 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "get_next_line.h"
# include "libft.h"
# include "op.h"
# include <stdbool.h>

typedef struct				s_func_list
{
	char					*name;
	char					*comment;
	t_direction				*info;
}							t_func_list;

typedef struct				s_direction
{
	unsigned char op_code;
	unsigned char encode;		// 1 byte // 
	int		arg_1;				// 1 byte // T_REG // 1 <-> 16 // unsigned 
	int		arg_2;				//	2 bytes // T_IND of T_DIR // // signed
	int		arg_3;				//	4 bytes  // T_DIR //	 signed
	int		has_label;
	char 	*label;
	char	*target_label;
	int		byte_index;
	int		byte_size;
	struct s_instruction * next
}							t_direction;

/*
**===============================ERROR FUNCTIONS================================
*/
void	input_error(void);

#endif
