/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cw_tester.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 10:25:07 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/02 10:26:13 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_TESTER_H
# define CW_TESTER_H
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef	struct	s_tester_vars
{
	char		*my_line;
	char		*cmp_line;
	int			my_ret;
	int			cmp_ret;
	int			i;
	int			faults;
}				t_tester_vars;

#endif
