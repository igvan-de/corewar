/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 10:23:59 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/02 10:26:56 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cw_tester.h"

static	void	put_lines(char *my_line, char *cmp_line, int *faults)
{
	if (ft_strcmp(my_line, cmp_line) != 0)
	{
		ft_putstr("	lines are not equal!\n");
		ft_putendl(my_line);
		ft_putendl(cmp_line);
		ft_putchar('\n');
		(*faults)++;
	}
}

static	void	cmp_lines(int my, int fd_cmp)
{
	t_tester_vars v;

	v.my_ret = get_next_line(my, &v.my_line);
	v.cmp_ret = get_next_line(fd_cmp, &v.cmp_line);
	v.i = 0;
	v.faults = 0;
	if (v.my_ret < 1 || v.cmp_ret < 1)
	{
		ft_putstr("cannot access file\n");
		return ;
	}
	while (v.my_ret > 0 && v.cmp_ret > 0)
	{
		put_lines(v.my_line, v.cmp_line, &v.faults);
		v.my_ret = get_next_line(my, &v.my_line);
		v.cmp_ret = get_next_line(fd_cmp, &v.cmp_line);
		v.i++;
	}
	if (v.faults == 0)
		ft_putstr("test passed!\n");
	else
		ft_printf("	%i output differences found --> test failed\n", v.faults);
}

static	void	parse_args(char *my, char *cmp)
{
	int		fd_my;
	int		fd_cmp;

	fd_my = open(my, O_RDONLY);
	if (fd_my == -1)
	{
		ft_printf("could not open my test output\n");
		exit(0);
	}
	fd_cmp = open(cmp, O_RDONLY);
	if (fd_my == -1)
	{
		ft_printf("could not open cmp test output\n");
		exit(0);
	}
	cmp_lines(fd_my, fd_cmp);
}

int				main(int argc, char **argv)
{
	if (argc != 3)
		ft_putendl("cw_tester could not execute --> argument count not right.");
	parse_args(argv[1], argv[2]);
	return (0);
}
