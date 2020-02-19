/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 09:01:48 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/18 09:01:50 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

//	op structure:
//		name, nb_params, params_type, id, cycles, discription, acb, label_size


static	t_op	get_op[17] =
{
	{{0}, 0, {0}, 0, 0, {0}, 0, 0},													//	id: 1 cycles: 10
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},										//	id: 1 cycles: 10
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},							//	id: 2 cycles: 5
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},							//	id: 3 cycles: 5
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition r1 + r2 -> r3", 1, 0},		//	id: 4 cycles: 10
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "subtraction r1 - r2 -> r3", 1, 0},	//	id: 5 cycles: 10
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,			//	id: 6 cycles: 6
	 "and  r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,			//	id: 7 cycles: 6
	 "or   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,			//	id: 8 cycles: 6
	 "xor  r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},								//  id: 9 cycles: 20
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,				//	id: 10 cycles: 25
	 "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,				//	id: 11 cycles: 25
	 "store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},									//	id: 12 cycles: 800
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},					//	id: 13 cycles: 10
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,				//	id: 14 cycles: 50
	 "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},								//	id: 15 cycles: 1000
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}											//	id: 16 cycles: 2
};

/*
**	load_optab receives a ptr to the global env struct and 
**	loads the operation reference table into its op_tab variable
*/

void	load_optab(t_env *env)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		env->op_tab[i] = get_op[i];
		i++;
	}
}