/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:55:12 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/29 16:30:47 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dist, const void *src, size_t n)
{
	unsigned char *pdist;
	unsigned char *psrc;

	pdist = (unsigned char*)dist;
	psrc = (unsigned char*)src;
	while (n--)
	{
		*pdist++ = *psrc++;
	}
	return (dist);
}
