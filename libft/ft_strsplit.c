/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 11:38:11 by mkrutik           #+#    #+#             */
/*   Updated: 2017/03/23 10:29:43 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		words(char const *s, char c)
{
	int		word;
	int		index;

	index = 0;
	word = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c && s[index + 1] != '\0' && s[index + 1] != '\0')
			word++;
		index++;
	}
	return (++word);
}

static	int		length(char const *s, int index, char c)
{
	int		result;

	result = 0;
	if (!*s)
		return (0);
	while (s[index] != '\0' && s[index] != c)
	{
		index++;
		result++;
	}
	return (result);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	char	*string;
	int		index;
	int		word;
	int		len;

	if (!s || (!(res = (char**)malloc(sizeof(char*) * words(s, c) + 1))))
		return (NULL);
	index = -1;
	word = 0;
	while (s[++index] != '\0')
		if (s[index] != c)
		{
			len = length(s, index, c);
			string = ft_strnew(len);
			ft_strncpy(string, s + index, len);
			string[len] = '\0';
			res[word++] = string;
			index += len - 1;
		}
	res[word] = NULL;
	return (res);
}
