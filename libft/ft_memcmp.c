/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:31:00 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/12/03 17:20:44 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*beer;
	unsigned char	*beer2;

	i = 0;
	beer = (unsigned char*)s1;
	beer2 = (unsigned char*)s2;
	while (n--)
	{
		if ((*beer > *beer2) || (*beer < *beer2))
			return (i = *beer - *beer2);
		beer++;
		beer2++;
	}
	return (i);
}
