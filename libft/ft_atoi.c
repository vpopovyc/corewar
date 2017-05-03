/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:38:37 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/10 15:04:10 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_atoi(const char *str)
{
	char	i;
	int		beer;

	i = 0;
	beer = 0;
	while ((((*str >= 9) && (*str <= 13)) || (*str == 32)) && (*str))
		str++;
	if (*str == 45)
		i = 1;
	if ((*str == 45) || (*str == 43))
		str++;
	while (((*str >= 48) && (*str <= 57)) && (*str))
	{
		beer = (beer * 10) + (*str - 48);
		str++;
	}
	if (i)
		return (beer = -beer);
	else
		return (beer);
}
