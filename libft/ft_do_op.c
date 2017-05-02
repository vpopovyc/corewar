/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:23:45 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/12/02 15:47:28 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

long	ft_do_op(char *n1, char *n2, char c)
{
	long		nb1;
	long		nb2;

	nb1 = ft_atoi(n1);
	nb2 = ft_atoi(n2);
	if (c == 42)
		return (nb1 = nb1 * nb2);
	if (c == 43)
		return (nb1 = nb1 + nb2);
	if (c == 45)
		return (nb1 = nb1 - nb2);
	if (c == 47)
		return (nb1 = nb1 - nb2);
	if (c == 37)
		return (nb1 = nb1 % nb2);
	return (0);
}
