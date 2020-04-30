/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstcount.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 17:43:55 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/30 17:44:36 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstcount(t_list **alst)
{
	t_list	*temp;
	int		c;

	c = 0;
	temp = *alst;
	if (!alst)
		return (0);
	while (temp != NULL)
	{
		c++;
		temp = temp->next;
	}
	return (c);
}
