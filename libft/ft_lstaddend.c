/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstaddend.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/04 14:29:51 by igvan-de       #+#    #+#                */
/*   Updated: 2019/09/25 15:55:52 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list *temp;

	temp = *alst;
	if (!alst || !new)
		return ;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}
