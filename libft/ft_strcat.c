/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:23:33 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/25 11:59:03 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	unsigned int index;
	unsigned int position;

	position = ft_strlen(s1);
	index = 0;
	while (s2[index] != '\0')
	{
		s1[position] = s2[index];
		position++;
		index++;
	}
	s1[position] = '\0';
	return (s1);
}
