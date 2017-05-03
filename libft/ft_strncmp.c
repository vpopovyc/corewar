/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:30:49 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/11/28 12:52:41 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				beer;
	unsigned char	*pt1;
	unsigned char	*pt2;

	pt1 = (unsigned char*)s1;
	pt2 = (unsigned char*)s2;
	while (((*pt1) || (*pt2)) && (n--))
	{
		if (*pt1 != *pt2)
		{
			beer = *pt1 - *pt2;
			return (beer);
		}
		pt1++;
		pt2++;
	}
	return (0);
}
