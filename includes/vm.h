/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vm.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 08:47:01 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/18 09:02:29 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

#include "libft.h"
#include "op.h"

/*
**	global environment struct containg main reference data and ptrs (initialized once)
*/

typedef struct	s_env
{
	t_op op_tab[17];
}				t_env;

void	load_optab(t_env *env);

#endif
