/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dsm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 12:50:39 by igor          #+#    #+#                 */
/*   Updated: 2020/04/30 12:38:13 by igor          ########   odam.nl         */
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

typedef struct		s_file
{
	header_t		*header;
	char			*args;
	t_op			op_tab[17];
	struct s_file	*next;
}					t_file;


/*
**===============================CREATING .S FUNCTIONS==========================
*/

void	write_s_file(int fd, t_file *file);
void	write_arg_s(int fd, unsigned prog_size, t_file *file);
void	load_optab_file(t_file *file);
int		create_s_file(char *argv);

#endif
