/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:01:33 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/02 16:47:21 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	size_t		i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s != c && *s)
				s++;
			if (*s == '\0')
				break ;
		}
		s++;
	}
	return (i);
}

static size_t	ft_count_chars(const char *s, char c)
{
	size_t		i;

	i = 0;
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**beer;
	size_t		len;
	size_t		i;

	if (!s)
		return (NULL);
	if (!(beer = (char**)malloc(sizeof(char*) * (ft_count_words(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			len = ft_count_chars(s, c);
			beer[i] = ft_strnew(len);
			ft_strncpy(beer[i++], s, len);
			s += len;
		}
		if (*s == '\0')
			break ;
		s++;
	}
	beer[i] = NULL;
	return (beer);
}
