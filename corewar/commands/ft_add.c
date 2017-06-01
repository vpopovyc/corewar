/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 12:40:54 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/01 12:41:15 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_add(t_corewar *data, t_carriage *src)
{
	if (data->field[src->position + 1] == 84)
	{
		ft_take_arg(data, src, 0, data->field[src->position]);
		if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0
			&& src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3]
			<= REG_NUMBER)
		{
			src->reg[src->arg[3]] = src->reg[src->arg[1]] +
				src->reg[src->arg[2]];
			src->carry = (src->reg[src->arg[3]] == 0) ? 1 : 0;
		}
	}
	else
		ft_inc_index(src);
	ft_bzero(src->arg, 16);
}
