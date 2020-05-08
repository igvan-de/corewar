/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_vars.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 12:31:32 by igor          #+#    #+#                 */
/*   Updated: 2020/05/02 17:23:14 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

void	free_vars(t_mainvars *v)
{
	free(v->fd_name);
	free(v->file->exec);
	free(v->file->header);
	free(v->file);
}
