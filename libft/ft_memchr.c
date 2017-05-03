/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:30:23 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/12/03 16:40:31 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	beer;

	beer = -1;
	while (++beer < n)
	{
		if (((unsigned char*)s)[beer] == (unsigned char)c)
			return ((void*)&s[beer]);
	}
	return (NULL);
}
