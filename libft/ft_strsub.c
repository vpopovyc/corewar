/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 18:18:40 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/25 11:12:10 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	index;
	char			*res;

	if (!s || !len || !(res = ft_strnew(len)))
		return (NULL);
	index = 0;
	while (index < len)
	{
		res[index] = s[start];
		start++;
		index++;
	}
	return (res);
}
