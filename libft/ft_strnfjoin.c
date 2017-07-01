/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnfjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 15:43:01 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/01/15 15:54:37 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnfjoin(char *s1, char *s2, size_t n)
{
	s1 = ft_realloc(s1, ft_strlen(s1) + n);
	s1 = ft_strncat(s1, s2, n);
	return (s1);
}
