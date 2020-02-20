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

/*
**	print header to stdout
*/

static	void	dump_header(header_t header)
{
	printf("\n	magic value: %#0x\n", rev_endian(header.magic));
	if (rev_endian(header.magic) == COREWAR_EXEC_MAGIC)
		ft_putendl("		---> magic is valid!\n");
	else
		ft_putendl("		---> error: magic is invalid!");
	printf("	name:				%s\n", header.prog_name);
	printf("	prog size:			%u\n", rev_endian(header.prog_size));
	printf("	comment:			%s\n", header.comment);
}

/*
**	open .cor file and parse header + execution code
*/

static	void	parse_champion(char *champ, t_env *env)
{
	int			fd;
	ssize_t		bytes;
	header_t	header;
	char		*prog_code;


	// open .cor
	fd = open(champ, O_RDONLY);
	printf("	opened %s at fd: %i\n", champ, fd);


	// read and print header
	bytes = read(fd, &header, sizeof(header_t));
	printf("		bytes read into header: %li\n", bytes);
	dump_header(header);


	// read and print execution code
	prog_code = ft_strnew(rev_endian(header.prog_size));
	bytes = read(fd, prog_code, rev_endian(header.prog_size));
	if (bytes != rev_endian(header.prog_size))
		ft_putendl("	error: actual size does not match header prog_size");
	printf("	execution code size:		%li\n", bytes);
	dump_prog_code(prog_code, rev_endian(header.prog_size), env);
}

/*
**	parse all arguments
*/

static	void	parse_args(int arg_nb, char **argv, t_env *env)
{
	int i;

	i = 1;
	while (i < arg_nb)
	{
		parse_champion(argv[i], env);
		ft_putchar('\n');
		i++;
	}
}

/*
**	main entry for corewar
*/

int				main(int argc, char **argv)
{
	t_env env;

	if (argc != 2)
		exit_usage();

	ft_putstr("\n\n<------------- Welcome to Corewar! ------------>\n\n");

	load_optab(&env);
	parse_args(argc, argv, &env);
	return (0);
}
