/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 19:05:14 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/03/18 19:05:55 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fdf.h"

void	ft_fdf(char *av)
{
	t_root	root;

	ft_get_root(0xffffff, 0xffffff, &root);
	if (ft_parse(open(av, O_RDONLY), &root))
	{
		if (((root.status ^ 0x2) ^ 0x80) & 0x40)
			exit(ft_printf("Invalid matrix\n"));
		if ((((root.status ^ 0x2) ^ 0x40) & 0x80) || !root.x_max)
			exit(ft_printf("Empty file\n"));
		if (((root.status ^ 0x40) ^ 0x80) & 0x2)
			ft_diagonal(&root);
	}
	ft_init_image(&root);
}
