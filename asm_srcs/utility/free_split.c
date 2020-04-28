/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 10:02:48 by mlokhors      #+#    #+#                 */
/*   Updated: 2020/04/09 04:04:00 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @brief
**
** @param fd_name = name of 2d char array containing splitted stings
**
** free_split frees every element in 2d array by iterating through it
*/

void	free_split(char **fd_name)
{
	int	index;

	index = 0;
	while (fd_name[index] != NULL)
	{
		free(fd_name[index]);
		index++;
	}
	free(fd_name);
	fd_name = NULL;
}
