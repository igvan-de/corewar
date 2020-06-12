/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_mem.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void		dump_addr_alt(unsigned int *bytes, int *addr_trig)
{
	if (*bytes == 0)
		ft_printf("0x0000 : ");
	else
		ft_printf("%#06x : ", *bytes);
	(*bytes) += 64;
	(*addr_trig) = 0;
}

static	void		dump_addr(unsigned int *bytes, int *addr_trig)
{
	if (*bytes == 0)
		ft_printf("0x0000 : ");
	else
		ft_printf("%#06x : ", *bytes);
	(*bytes) += 32;
	(*addr_trig) = 0;
}

void				dump_mem_alt(t_env *env)
{
	int				i;
	int				addr_trig;
	unsigned int	bytes;

	i = 0;
	addr_trig = 1;
	bytes = 0;
	while (i < MEM_SIZE)
	{
		if (addr_trig == 1)
			dump_addr_alt(&bytes, &addr_trig);
		if (env->datamap[i].player != 0)
			ft_printf("%02x ", 0xFF & env->map[i]);
		else
			ft_printf("%#02x ", env->map[i]);
		if ((i + 1) % 64 == 0)
		{
			addr_trig = 1;
			ft_putchar('\n');
		}
		i++;
	}
	exit(0);
}

/*
**	@brief:	dump_mem prints memory to stdout
**
**	@param env		:	global environment struct
**
**	dump_mem is a debug function that can be used to
**	print the current state of memory to stdout. This function
**	is also called when the '-dump' flag is enabled.
*/

void				dump_mem(t_env *env)
{
	int				i;
	int				addr_trig;
	unsigned int	bytes;

	i = 0;
	addr_trig = 1;
	bytes = 0;
	while (i < MEM_SIZE)
	{
		if (addr_trig == 1)
			dump_addr(&bytes, &addr_trig);
		if (env->datamap[i].player != 0)
			ft_printf("%02x ", 0xFF & env->map[i]);
		else
			ft_printf("%#02x ", env->map[i]);
		if ((i + 1) % 32 == 0)
		{
			addr_trig = 1;
			ft_putchar('\n');
		}
		i++;
	}
	exit(0);
}

/*
**	@brief:	print player positions to stdout
**
**	@param env		:	global environment struct
**
**	dump_pos is a debug function that can be used
**	to print player positions as stored in env->datamap to stdout.
*/

void				dump_pos(t_env *env)
{
	int				i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%hhi ", env->datamap[i].player);
		if ((i + 1) % 64 == 0)
			ft_putchar('\n');
		i++;
	}
}
