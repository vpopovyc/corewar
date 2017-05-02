/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:33:40 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/11/28 12:51:10 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*beer;

	beer = NULL;
	if (s1 && s2)
	{
		i = ft_strlen(s1) + ft_strlen(s2);
		if ((beer = ft_strnew(i)))
			beer = ft_strcat(ft_strcpy(beer, s1), s2);
	}
	return (beer);
}
