/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 11:41:46 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/11/29 12:41:35 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*beer;
	t_list		*head;

	if (!(lst) || (!(f)))
		return (NULL);
	beer = f(lst);
	head = beer;
	lst = lst->next;
	while (lst)
	{
		beer->next = f(lst);
		beer = beer->next;
		lst = lst->next;
	}
	return (head);
}
