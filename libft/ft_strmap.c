/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:10:14 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/11/25 17:32:21 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*beer;
	size_t	i;

	i = -1;
	beer = NULL;
	if (s && f)
	{
		if (!(beer = ft_strnew(ft_strlen(s))))
			return (NULL);
		while (s[++i])
			beer[i] = f(s[i]);
	}
	return (beer);
}
