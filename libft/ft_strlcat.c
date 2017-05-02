/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 21:08:56 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/12/02 14:46:45 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*beer;
	size_t	beer2;
	size_t	beer3;

	beer = dst;
	beer2 = ft_strlen(beer);
	beer3 = size - beer2;
	if (beer3 > 0)
	{
		ft_strncat(dst, src, beer3 - 1);
		return (ft_strlen(src) + beer2);
	}
	else
		return (ft_strlen(src) + size);
}
