/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:23:12 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/11/25 14:33:53 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnew(size_t size)
{
	char	*beer;

	if (!(beer = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(beer, size + 1);
	return (beer);
}
