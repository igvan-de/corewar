/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dsm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 12:50:39 by igor          #+#    #+#                 */
/*   Updated: 2020/04/29 12:40:59 by igor          ########   odam.nl         */
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

typedef struct	s_test
{
	header_t	*header;
}				t_test;


/*
**===============================CREATING .S FUNCTIONS==========================
*/

void	write_s_file(int fd, header_t *header);
int		create_s_file(char *argv);

#endif
