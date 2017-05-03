/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:50:51 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/29 16:56:55 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

char			*ft_strtrim(char const *s)
{
	unsigned int	start;
	unsigned int	finish;
	unsigned int	len;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] != '\0' && whitespace(s[start]))
		start++;
	finish = ft_strlen(s);
	while (start < finish && whitespace(s[finish - 1]))
		finish--;
	if (start == finish)
		return (ft_strnew(1));
	len = finish - start;
	return (ft_strsub(s, start, len));
}
