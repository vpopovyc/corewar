/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 12:50:47 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/01 12:50:49 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_ld_1(t_corewar *data, t_carriage *src)
{
	ft_take_arg(data, src, 0, data->field[src->position]);;
	(src->arg[1] > IDX_MOD) ? (src->arg[1] %= IDX_MOD) : 0;
	if (src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER)
	{
		src->reg[src->arg[2]] = ((unsigned char)data->field[
			ft_fix(src->position - 5 + src->arg[1])] << 24) |
			((unsigned char)data->field[ft_fix(src->position - 5
			+ src->arg[1] + 1)] << 16) | ((unsigned char)data->field[
			ft_fix(src->position - 5 + src->arg[1] + 2)] << 8) |
			(unsigned char)data->field[ft_fix(src->position - 5 +
			src->arg[1] + 3)];
		src->carry = (src->reg[src->arg[2]] == 0) ? 1 : 0;
	}
}

void	ft_ld(t_corewar *data, t_carriage *src)
{
	if (data->field[src->position + 1] == -48)
		ft_1(data, src);
	else if (data->field[src->position + 1] == -112)
	{
		ft_take_arg(data, src, 0, data->field[src->position]);
		if (src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER)
		{
			src->reg[src->arg[2]] = src->arg[1];
			src->carry = (src->reg[src->arg[2]] == 0) ? 1 : 0;
		}
	}
	else
		ft_inc_index(src);
	ft_bzero(src->arg, 16);
}
