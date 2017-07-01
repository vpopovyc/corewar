/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:10:38 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/11/24 22:14:32 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t beer;

	if (!(*little))
		return ((char*)big);
	beer = ft_strlen(little);
	while (*big)
	{
		if (!(ft_strncmp(big, little, beer)))
			return ((char*)big);
		big++;
	}
	return (NULL);
}
