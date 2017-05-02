/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:13:24 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/06 15:11:13 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		i;
	char		*beer;

	i = ft_strlen(s1);
	beer = (char*)malloc(sizeof(char) * (i + 1));
	if (beer)
	{
		*beer = *ft_strcpy(beer, s1);
		return (beer);
	}
	else
		return (NULL);
}
