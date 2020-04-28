/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/14 08:08:05 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/14 08:08:31 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**	The main function of this library, ft_printf is able to print
**	a variadic number of arguments given as elements to be accessed sequentially
**	in the order specified in the input string 'format'. ft_print will
**	look for as many arguments within the variadic list as the count of '%'s
**	within the format string. The return value for this function is the
**	total number of characters printed or the 'real' length of the format
**	string with converted arguments included.
*/

int		ft_printf(const char *format, ...)
{
	char	*dest;
	int		len;
	va_list	a_list;

	dest = 0;
	va_start(a_list, format);
	len = ft_vasprintf(&dest, format, a_list, 0);
	va_end(a_list);
	return (len);
}
