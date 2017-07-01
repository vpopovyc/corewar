/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 19:37:00 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/01/23 20:05:22 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int		ft_len(size_t v, size_t b)
{
	int		ln;

	ln = (v == 0) ? 1 : 0;
	while (v)
	{
		v /= b;
		++ln;
	}
	return (ln);
}

char			*ft_stoab(size_t v, size_t b)
{
	int			ln;
	char		*st;

	if (b < 2 || b > 16)
		return (NULL);
	ln = ft_len(v, b);
	st = ft_strnew(ln);
	while (--ln >= 0)
	{
		st[ln] = ((v % b) > 9) ? ((v % b) - 10 + 'A') : ((v % b) + '0');
		v /= b;
	}
	return (st);
}
