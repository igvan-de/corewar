/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 08:46:02 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/18 08:46:39 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

static	void	print_op_name(t_env *env)
{
	int i;
	t_op curr_op;

	i = 0;
	while (i < 16)
	{
		curr_op = env->op_tab[i];
		ft_putendl(curr_op.name);
		i++;
	}
}

# define BUFF_SIZE 1024


static	void	parse_args(int arg_nb, char **argv)
{
	int fd;
	ssize_t bytes;
	unsigned int *buf;

	printf("	parse args is called with %i arguments\n", arg_nb);

	buf = 0;
	if (arg_nb > 0)
	{
		printf("	trying to open %s\n", argv[1]);
		fd = open(argv[1], O_RDONLY);
		printf("	new fd was opened at %i\n", fd);
		bytes = read(fd, &buf, sizeof(BUFF_SIZE));
		printf("	%li bytes read into buff: %u\n", bytes, (unsigned int)buf);
		while (bytes > 0)
		{
			bytes = read(fd, buf, sizeof(BUFF_SIZE));
			printf("	%li bytes read into buff: %u\n", bytes, (unsigned int)buf);
		}
	}
}

int main(int argc, char **argv)
{
	t_env env;
	ft_putstr("Welcome to Corewar!\n");
	
	load_optab(&env);
	print_op_name(&env);
	parse_args(argc, argv);
	return (0);
}
