/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:14:26 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/29 16:39:08 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *pdest;
	unsigned char *psrc;

	pdest = (unsigned char*)dest;
	psrc = (unsigned char*)src;
	if (psrc < pdest)
	{
		pdest += n;
		psrc += n;
		while (n--)
			*--pdest = *--psrc;
	}
	else
		while (n--)
		{
			*pdest++ = *psrc++;
		}
	return (dest);
}
