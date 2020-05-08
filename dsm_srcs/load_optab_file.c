/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_optab_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 12:35:18 by igor          #+#    #+#                 */
/*   Updated: 2020/04/30 15:36:12 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

/*
**	@brief: retrieve operation reference table
**
**	@param file	: global file struct
**
**	load_optab receives a ptr to the global file struct and
**	loads the operation reference table into its op_tab variable
*/

static	void	transfer_opdata_file(t_op get_op[17], t_file *file)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		file->op_tab[i] = get_op[i];
		i++;
	}
}

void			load_optab_file(t_file *file)
{
	static	t_op	get_op[17] = {{{0}, 0, {0}, 0, 0, {0}, 0, 0},
		{"live", 1, {T_DIR}, 1, 10, "", 0, 0},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "", 1, 0},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "", 1, 0},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "", 1, 0},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "", 1, 0},
		{"and", 3, {ALL, ALL, T_REG}, 6, 6, "", 1, 0},
		{"or", 3, {ALL, ALL, T_REG}, 7, 6, "", 1, 0},
		{"xor", 3, {ALL, ALL, T_REG}, 8, 6, "", 1, 0},
		{"zjmp", 1, {T_DIR}, 9, 20, "", 0, 1},
		{"ldi", 3, {ALL, T_DIR | T_REG, T_REG}, 10, 25, "", 1, 1},
		{"sti", 3, {T_REG, ALL, T_DIR | T_REG}, 11, 25, "", 1, 1},
		{"fork", 1, {T_DIR}, 12, 800, "", 0, 1},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "", 1, 0},
		{"lldi", 3, {ALL, T_DIR | T_REG, T_REG}, 14, 50, "", 1, 1},
		{"lfork", 1, {T_DIR}, 15, 1000, "", 0, 1},
		{"aff", 1, {T_REG}, 16, 2, "", 1, 0}};

	transfer_opdata_file(get_op, file);
}
