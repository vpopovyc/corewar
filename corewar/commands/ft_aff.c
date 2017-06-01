/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 12:40:19 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/01 16:45:19 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_aff(t_corewar *data, t_carriage *src)
{
	ft_inc_index(src);
	if (data->field[src->position] == 64)
	{
		ft_inc_index(src);
		src->arg[1] = data->field[ft_inc_index(src)];
		if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
			ft_printf("%c", src->reg[src->arg[1]] % 256);
	}
	ft_bzero(src->arg, 16);
}
