/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_labs.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 17:43:55 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/30 17:44:36 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	ft_labs (long absolute) returns the absolute value of the argument.
*/

long	int	ft_labs(long int nb)
{
	if (nb < 0)
		return (nb * -1);
	else
		return (nb);
}
