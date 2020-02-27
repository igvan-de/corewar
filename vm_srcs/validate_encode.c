/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_encode.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 13:28:49 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 13:28:50 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	validate_arg receives the arg value stored in the operations,
**	op_tab entry and checks if the related bitpair in the encode byte
**	matches the op_tab entry. returns 1 if match, 0 if it does not match.
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
**	validate_encode receives the encode byte of an operation and
**	checks if that encode byte is valid. returns 1 if valid and
**	returns 0 if the encode byte is invalid.
*/

int			valid_encode(BYTE op_code, BYTE encode, t_env *env)
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
