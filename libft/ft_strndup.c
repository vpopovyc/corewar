/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:02:23 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/09 15:17:13 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strndup(char *sv, size_t n)
{
	char	*rs;

	rs = sv == NULL ? NULL : (char*)malloc(sizeof(char) * (n + 1));
	rs[n] = '\0';
	rs = ft_strncpy(rs, sv, n);
	return (rs);
}
