/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 12:49:53 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/29 10:34:25 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *find, size_t len)
{
	char			*ps;
	unsigned int	len_find;

	ps = (char*)s;
	if (!*ps && !*find)
		return (ps);
	len_find = ft_strlen(find);
	while (*ps && len >= len_find)
	{
		if (!(ft_strncmp(ps, find, len_find)))
			return (ps);
		ps++;
		len--;
	}
	return (NULL);
}
