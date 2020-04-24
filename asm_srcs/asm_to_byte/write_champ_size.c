/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_champ.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:37:30 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/20 16:42:17 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief writes size of executable champion commands into filediscriptor
**
** @param fd			= filediscripter to write string in
** @param champ_size	= size of the champion
**
** write_champ_size writes the size of only executable
** part of champion in filediscriptor.
*/

void	write_champ_size(int fd, int champ_size)
{
	champ_size = rev_endian(champ_size);
	write(fd, &champ_size, 4);
}
