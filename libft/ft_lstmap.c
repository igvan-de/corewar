/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/04 11:26:03 by igvan-de       #+#    #+#                */
/*   Updated: 2019/09/25 16:00:16 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_node;
	t_list *head;

	if (!lst || !f)
		return (NULL);
	head = f(lst);
	lst = lst->next;
	while (lst != NULL)
	{
		new_node = f(lst);
		lst = lst->next;
		ft_lstaddend(&head, new_node);
	}
	return (head);
}
