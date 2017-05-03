/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 20:16:49 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/11/28 12:46:41 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int		ft_get_len(long tmp)
{
	int		i;

	i = 0;
	if (tmp <= 0)
	{
		i++;
		tmp = -tmp;
	}
	while (tmp)
	{
		tmp = tmp / 10;
		i++;
	}
	return (i);
}

static void		ft_beer(char *s, long tmp, int i)
{
	if (tmp >= 10)
	{
		ft_beer(s, tmp / 10, i - 1);
		ft_beer(s, tmp % 10, i);
	}
	if (tmp < 10)
		s[i - 1] = tmp + 48;
}

char			*ft_itoa(int n)
{
	int		blen;
	long	temp;
	char	*beer;

	temp = n;
	blen = ft_get_len(temp);
	beer = ft_strnew(blen);
	if (!beer)
		return (NULL);
	beer[blen] = '\0';
	if (temp < 0)
	{
		temp = -temp;
		beer[0] = '-';
	}
	ft_beer(beer, temp, blen);
	return (beer);
}
