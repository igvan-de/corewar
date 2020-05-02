/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dsm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 12:50:39 by igor          #+#    #+#                 */
/*   Updated: 2020/05/02 14:23:49 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DSM_H
# define DSM_H

# include <stdint.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "op.h"
# include "asm.h"
# include <stdbool.h>
# include <fcntl.h>

typedef enum		e_type
{
	NONE = 0,
	REG = 1,
	IND = 2,
	DIR = 3
}					t_type;

typedef struct		s_file
{
	header_t		*header;
	char			*exec;
	int 			arg_size;
	t_type			type;
	t_op			op_tab[17];
}					t_file;

/*
**===============================CREATING .S FUNCTIONS==========================
*/

void	write_s_file(int fd_s, t_file *file);
void	write_arg_s(int fd_s, unsigned prog_size, t_file *file);
void	load_optab_file(t_file *file);
int		create_s_file(char *argv);
int		convert(int index, char *exec, int arg_size);

#endif
