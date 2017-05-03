/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 12:43:53 by mkrutik           #+#    #+#             */
/*   Updated: 2016/12/01 15:18:26 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *src1, const char *src2, size_t n)
{
	if (n == 0)
		return (0);
	while (n != 0)
	{
		if (*src1 != *src2++)
			return (*(unsigned char*)src1 - *(unsigned char*)--src2);
		if (*src1++ == 0)
			return (0);
		n--;
	}
	return (0);
}
