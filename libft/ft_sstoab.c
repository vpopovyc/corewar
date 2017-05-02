/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sstoab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:18:54 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/01/29 22:00:41 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int		ft_len(ssize_t value, ssize_t base)
{
	int		len;

	len = (value == 0) ? 1 : 0;
	while (value)
	{
		value /= base;
		++len;
	}
	return (len);
}

char			*ft_sstoab(ssize_t value, ssize_t base)
{
	size_t		t;
	char		fs;
	int			ln;
	char		*st;
	char		b;

	if (base < 2 || base > 16)
		return (NULL);
	b = base;
	t = (value < 0) ? -value : value;
	fs = (value < 0 && b == 10) ? 1 : 0;
	ln = (value < 0) ? (ft_len(t, b) + 1) : (ft_len(t, b));
	st = ft_strnew(ln);
	(fs == 1) ? st[0] = '-' : 0;
	while (--ln >= fs)
	{
		st[ln] = ((t % b) > 9) ? ((t % b) - 10 + 'A') : ((t % b) + '0');
		t /= b;
	}
	return (st);
}
