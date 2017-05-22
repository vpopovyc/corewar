/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:07:02 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/11/28 12:49:53 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int					i;
	unsigned char		*pt1;
	unsigned char		*pt2;

	pt1 = (unsigned char*)s1;
	pt2 = (unsigned char*)s2;
	while ((*pt1) || (*pt2))
	{
		if (*pt1 != *pt2)
		{
			i = *pt1 - *pt2;
			return (i);
		}
		pt1++;
		pt2++;
	}
	return (0);
}
