/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 22:30:57 by vpopovyc          #+#    #+#             */
/*   Updated: 2016/11/28 12:43:49 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	b;

	b = n;
	if (b < 0)
	{
		ft_putchar_fd('-', fd);
		b = -b;
	}
	if (b >= 10)
	{
		ft_putnbr_fd((int)b / 10, fd);
		ft_putnbr_fd(b % 10, fd);
	}
	if (b < 10)
		ft_putchar_fd((b += 48), fd);
}
