/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:39:04 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/01 13:39:09 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_zjmp(t_corewar *data, t_carriage *src)
{
	ft_inc_index(src);
	if (src->carry == 1)
	{
		src->arg[1] = (data->field[ft_inc_index(src)] << 8) |
			data->field[ft_inc_index(src)];
		src->position = ft_fix(src->position - 3 + src->arg[1]);
		ft_bzero(src->arg, 16);
	}
	else
		src->position = ft_fix(src->position + 2);
}
