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
# include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

static	void	cmp_lines(int my, int fd_cmp)
{
	char *my_line;
	char	*cmp_line;
	int	my_ret;
	int	cmp_ret;
	int	i;
	int	faults;

	my_ret = get_next_line(my, &my_line);
	cmp_ret = get_next_line(fd_cmp, &cmp_line);
	i = 0;
	faults = 0;
	if (my_ret < 1 || cmp_ret < 1)
	{
		ft_putstr("cannot access file\n");
		return ;
	}
	while (my_ret > 0 && cmp_ret > 0)
	{
		if (ft_strcmp(my_line, cmp_line) != 0)
		{
			ft_putstr("	lines are not equal!\n");
			ft_putendl(my_line);
			ft_putendl(cmp_line);
			ft_putchar('\n');
			faults++;
		}
		my_ret = get_next_line(my, &my_line);
		cmp_ret = get_next_line(fd_cmp, &cmp_line);
		i++;
	}
	if (faults == 0)
		ft_putstr("test passed!\n");
	else
		printf("	%i output differences found --> test failed\n", faults);
}

static	void	parse_args(char *my, char *cmp)
{
	int		fd_my;
	int		fd_cmp;

	fd_my = open(my, O_RDONLY);
	if (fd_my == -1)
	{
		printf("could not open my test output\n");
		exit (0);
	}
	fd_cmp = open(cmp, O_RDONLY);
	if (fd_my == -1)
	{
		printf("could not open cmp test output\n");
		exit (0);
	}
	cmp_lines(fd_my, fd_cmp);
}

int main(int argc, char **argv)
{	
	if (argc != 3)
		ft_putendl("cw_tester could not execute --> argument count not right.");
	parse_args(argv[1], argv[2]);
	return (0);
}


