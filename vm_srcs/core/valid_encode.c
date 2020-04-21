/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_encode.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	validate encoding byte bitpair
**
**	@param arg	:	operation table reference
**	@param bit1	:	first bit of bitpair
**	@param bit2 :	second bit of bitpair
**
**	validate_arg receives a bitpair and checks if that
**	bitpair is a valid match to the arg bitpair passed as parameter.
*/

static	int	validate_arg(unsigned char arg, int bit1, int bit2)
{
	unsigned char bitpair;

	bit1 <<= 1;
	bitpair = (unsigned char)bit1 | bit2;
	if (bitpair == 3)
		bitpair = 4;
	if ((arg == 0 && bitpair != 0) || (bitpair == 0 && arg != 0))
		return (0);
	if (arg == T_REG && bitpair != T_REG)
		return (0);
	if (arg == T_DIR && bitpair != T_DIR)
		return (0);
	if (arg == T_IND && bitpair != T_IND)
		return (0);
	if (arg == (T_DIR | T_REG) && bitpair == T_IND)
		return (0);
	if (arg == (T_IND | T_REG) && bitpair == T_DIR)
		return (0);
	if (arg == (T_DIR | T_IND) && bitpair == T_REG)
		return (0);
	return (1);
}

/*
**	@brief: validate the encoding byte of an operation
**
**	@param op_code		:	operatione code byte
**	@param encode		:	encode byte
**	@param env			:	global environment struct
**
**	validate_encode receives an operation code and an encoding byte
**	and checks if the encoding byte is a valid match to the operation code
**	given by checking values against the operations reference table.
*/

int			valid_encode(t_byt op_code, t_byt encode, t_env *env)
{
	unsigned char	arg;
	int				nb_params;

	if (get_bit(encode, 6) != 0 || get_bit(encode, 7) != 0)
		return (0);
	arg = 0;
	nb_params = env->op_tab[op_code].nb_params;
	if (nb_params >= 1)
		arg = env->op_tab[op_code].params_type[0];
	if (validate_arg(arg, get_bit(encode, 0), get_bit(encode, 1)) == 0)
		return (0);
	arg = 0;
	if (nb_params >= 2)
		arg = env->op_tab[op_code].params_type[1];
	if (validate_arg(arg, get_bit(encode, 2), get_bit(encode, 3)) == 0)
		return (0);
	arg = 0;
	if (nb_params >= 3)
		arg = env->op_tab[op_code].params_type[2];
	if (validate_arg(arg, get_bit(encode, 4), get_bit(encode, 5)) == 0)
		return (0);
	return (1);
}
