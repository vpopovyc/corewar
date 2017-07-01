/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:32:33 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/06/05 14:30:40 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *beer;

	if (b)
	{
		beer = (unsigned char*)b;
		while (len--)
		{
			*beer = c;
			beer++;
		}
	}
	return (b);
}
