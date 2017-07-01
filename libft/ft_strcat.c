/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 19:38:58 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/12/02 14:43:52 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char *beer;

	beer = s1;
	beer = beer + ft_strlen(s1);
	while (*s2)
	{
		*beer = *s2;
		beer++;
		s2++;
	}
	*beer = '\0';
	return (s1);
}
