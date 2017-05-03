/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:45:19 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/24 17:56:07 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*res;

	index = 0;
	if (!s || !(res = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[index])
	{
		res[index] = (f)(index, s[index]);
		index++;
	}
	return (res);
}
