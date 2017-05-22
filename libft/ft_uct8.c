/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uct8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 17:04:08 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/01/29 20:58:37 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_uct8(wchar_t c, unsigned char *data, char n)
{
	if (n == 1)
		*data = (unsigned char)(c);
	else if (n == 2)
	{
		*data = (unsigned char)((c >> 6) | 0xC0);
		*(++data) = (unsigned char)((c & 0x3F) | 0x80);
	}
	else if (n == 3)
	{
		*data = (unsigned char)((c >> 12) | 0xE0);
		*(++data) = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
		*(++data) = (unsigned char)((c & 0x3f) | 0x80);
	}
	else if (n == 4)
	{
		*data = (unsigned char)((c >> 18) | 0xF0);
		*(++data) = (unsigned char)(((c >> 12) & 0x3F) | 0x80);
		*(++data) = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
		*(++data) = (unsigned char)((c & 0x3F) | 0x80);
	}
	*(++data) = '\0';
	return ((char*)data - n);
}
