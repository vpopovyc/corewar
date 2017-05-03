/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:28:31 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/29 15:54:58 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	size;
	char	*copy;

	size = ft_strlen(str) + 1;
	copy = (char*)malloc(sizeof(char) * size);
	if (copy == NULL)
	{
		return (NULL);
	}
	ft_memcpy(copy, str, size);
	return (copy);
}
