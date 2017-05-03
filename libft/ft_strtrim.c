/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:57:21 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/11/28 12:59:54 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(char const *s)
{
	char	*beer;
	int		st;
	int		ed;

	if (!s)
		return (NULL);
	st = 0;
	ed = (int)ft_strlen(s) - 1;
	while (s[st] && (s[st] == ' ' || s[st] == '\n' || s[st] == '\t'))
		st++;
	if (st == (int)ft_strlen(s))
		return (ft_strnew(0));
	while (s[ed] && (s[ed] == ' ' || s[ed] == '\n' || s[ed] == '\t'))
		ed--;
	beer = ft_strsub(s, st, ed - st + 1);
	return (beer);
}
