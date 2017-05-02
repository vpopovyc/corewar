/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscl_group3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 13:17:42 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/01/29 21:08:34 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_iscl_group3(char c)
{
	if ((ft_isascii(c) && !ft_iscl_group1(c) && !ft_iscl_group2(c)))
		return (1);
	return (0);
}
