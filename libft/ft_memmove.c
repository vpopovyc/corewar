/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:31:50 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/12/03 16:45:47 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	b;

	b = -1;
	if (dst < src)
		while (++b < len)
			((unsigned char*)dst)[b] = ((unsigned char*)src)[b];
	else
		while (++b < len)
			((unsigned char*)dst)[len - b - 1] =
				((unsigned char*)src)[len - b - 1];
	return (dst);
}
