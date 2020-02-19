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

//	reverse endian

unsigned int little_big(unsigned int little)
{
    return((little&0xff)<<24)+((little&0xff00)<<8)+((little&0xff0000)>>8)+      \
                                                             ((little>>24)&0xff);
}

//	print header to stdout

static	void	dump_header(header_t header)
{
	printf("	header has magic: %#0x\n", little_big(header.magic));
	if (little_big(header.magic) == COREWAR_EXEC_MAGIC)
		printf("	---> magic is valid!\n");
	else
		printf("	---> error: magic is invalid!\n");
	printf("	header has name:	%s\n", header.prog_name);
	printf("	header has prog size: %u\n", little_big(header.prog_size));
	printf("	header has comment: %s\n", header.comment);
}

//	open argument and parse the champion

static	void	parse_champion(char *arg, t_env *env)
{
	int			fd;
	ssize_t		bytes;
	header_t	header;
	char		*prog_code;

	fd = open(arg, O_RDONLY);
	printf("	opened file %s at fd: %i in parse_header\n", arg, fd);
	bytes = read(fd, &header, sizeof(header_t));
	printf("		bytes read into header: %li\n", bytes);
	dump_header(header);

	prog_code = ft_strnew(little_big(header.prog_size));
	bytes = read(fd, prog_code, little_big(header.prog_size));
	if (bytes != little_big(header.prog_size))
		printf("	error: actual prog_size does not match header prog_size variable\n");
	printf("	total bytes read into prog_code: %li\n", bytes);
	dump_prog_code(prog_code, little_big(header.prog_size), env);	
}

//	parse all arguments

static	void	parse_args(int arg_nb, char **argv, t_env *env)
{
	int i;

	printf("	parse args is called with %i arguments\n\n\n", arg_nb - 1);

	i = 1;
	while (i < arg_nb)
	{
		parse_champion(argv[i], env);
		ft_putchar('\n');
		i++;
	}
}

//	main entry for corewar

int main(int argc, char **argv)
{
	t_env env;
	ft_putstr("\n\n<------------------------- Welcome to Corewar! ---------------------->\n\n\n");

	load_optab(&env);
	parse_args(argc, argv, &env);
	return (0);
}
