/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 14:22:59 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/12/02 14:56:58 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*beer;
	int		beer2;

	beer2 = (int)ft_strlen(s);
	while (beer2-- >= 0)
	{
		if (*s == c)
		{
			beer = (char*)s;
			return (beer);
		}
		s++;
	}
	return (NULL);
}
