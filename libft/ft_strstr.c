/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 11:31:10 by mkrutik           #+#    #+#             */
/*   Updated: 2016/12/01 13:21:00 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s, const char *find)
{
	char			*ps;
	unsigned int	len_find;

	ps = (char*)s;
	if (!*ps && !*find)
		return (ps);
	len_find = ft_strlen(find);
	while (*ps)
	{
		if (!(ft_strncmp(ps, find, len_find)))
			return (ps);
		ps++;
	}
	return (NULL);
}
