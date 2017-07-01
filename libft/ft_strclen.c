/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:39:05 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/03/23 19:02:34 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strclen(char *sv, char c)
{
	char	*tmp;

	tmp = sv;
	while (*tmp)
	{
		if (*tmp == c)
			break ;
		++tmp;
	}
	return (tmp - sv);
}
