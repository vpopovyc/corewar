/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:58:40 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/25 12:27:02 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	unsigned int position;
	unsigned int index;

	position = ft_strlen(s1);
	index = 0;
	while (n && s2[index])
	{
		s1[position] = s2[index];
		position++;
		index++;
		n--;
	}
	s1[position] = '\0';
	return (s1);
}
