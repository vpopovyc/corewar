/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:33:00 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/28 17:15:36 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		count_len(int n)
{
	size_t			i;
	unsigned int	un;

	i = 1;
	un = n;
	if (n < 0)
	{
		un = -n;
		i++;
	}
	while ((un /= 10) >= 1)
		i++;
	return (i);
}

char				*ft_itoa(int n)
{
	unsigned int	un;
	int				len;
	int				start;
	char			*ptr;

	len = count_len(n);
	un = n;
	start = 0;
	if ((ptr = (char*)malloc(len + 1)))
	{
		ptr[len] = '\0';
		if (n < 0)
		{
			ptr[0] = '-';
			un = -n;
			start = 1;
		}
		while (len-- > start)
		{
			ptr[len] = (un % 10) + 48;
			un /= 10;
		}
		return (ptr);
	}
	return (NULL);
}
