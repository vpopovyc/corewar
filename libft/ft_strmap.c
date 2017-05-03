/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:16:05 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/24 17:44:53 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	index;
	char			*res;

	index = 0;
	if (!s || !(res = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[index])
	{
		res[index] = (f)(s[index]);
		index++;
	}
	return (res);
}
