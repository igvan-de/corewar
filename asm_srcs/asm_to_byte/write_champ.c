/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_champ.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:37:30 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/11 10:02:51 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief writes size of executable champion commands into filediscriptor
**
** @param fd = filediscripter to write string in
** @param champ_size = size of the champion
**
** write_champ_size writes the size of only executable part of champion in filediscriptor
** it write the champ_size of a four byte size
*/

void	write_champ_size(int fd, int champ_size)
{
	if (champ_size > CHAMP_MAX_SIZE)
	/*need to place error message, need to give t_func_struct, but need to know where to find champ size in info*/
	{
		ft_putendl("champion is to big");
		exit(-1);
	}
	champ_size = rev_endian(champ_size);
	write(fd, &champ_size , 4);
}

/*
** @brief writes executable champion commands in byte_code into filediscriptor
**
** @param fd
** @param list
**
** write_champ writes all the labels and operations into byte_code into the filediscriptor
*/

void	write_champ(int fd, t_func_list *list)
{
	if (list->info->label != NULL)
		write(fd ,&list->info->label, 4);
	if (list->info->arg_1 != NULL)
		write(fd, &list->info->arg_1, list->info->arg_1_number);
	if (list->info->arg_2 != NULL)
		write(fd, &list->info->arg_2, list->info->arg_2_number);
	if (list->info->arg_2 != NULL)
		write(fd, &list->info->arg_2, list->info->arg_2_number);
}
