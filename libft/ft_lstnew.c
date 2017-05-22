/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 21:05:37 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/11/28 22:06:12 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*beer;

	beer = (t_list*)malloc(sizeof(t_list));
	if (beer)
	{
		if (!(content))
		{
			beer->content_size = 0;
			beer->content = NULL;
		}
		else
		{
			beer->content = malloc(content_size);
			ft_memcpy(beer->content, content, content_size);
			beer->content_size = content_size;
		}
		beer->next = NULL;
		return (beer);
	}
	return (NULL);
}
