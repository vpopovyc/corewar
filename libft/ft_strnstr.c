/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 12:42:41 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/12/04 18:26:55 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	beer;

	i = 0;
	j = 0;
	if (ft_strlen(little) == 0)
		return ((char*)big);
	while (big[i] && i <= len)
	{
		beer = i;
		while (little[j] == big[i] && little[j] && i < len)
		{
			j++;
			i++;
		}
		if (j == ft_strlen(little))
			return ((char*)&big[i - j]);
		j = 0;
		i = beer + 1;
	}
	return (NULL);
}
