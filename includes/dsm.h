/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dsm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 12:50:39 by igor          #+#    #+#                 */
/*   Updated: 2020/05/02 17:18:31 by igor          ########   odam.nl         */
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
	t_header		*header;
	char			*exec;
	t_type			type;
	t_op			op_tab[17];
}					t_file;

typedef	struct		s_mainvars
{
	char			*fd_name;
	int				fd_s;
	int				fd_cor;
	ssize_t			bytes;
	t_file			*file;
	unsigned int	exec_code_size;
}					t_mainvars;

/*
**===============================DSM==========================
*/

void				write_s_file(int fd_s, t_file *file);
void				write_args_into_s(int fd_s, unsigned p_size, t_file *f);
void				load_optab_file(t_file *file);
int					create_s_file(char *argv);
int					convert(int index, char *exec, int arg_size);
int					get_arg_value(t_file *file, int op_code, int one, int two);
char				*file_check(char *argv);
void				free_vars(t_mainvars *v);

#endif
