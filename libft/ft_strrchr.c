/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 10:57:59 by mkrutik           #+#    #+#             */
/*   Updated: 2016/12/01 13:08:18 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *res;

	res = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			res = (char*)s;
		s++;
	}
	if (!*s && c == '\0')
		return ((char*)s);
	return (res);
}
