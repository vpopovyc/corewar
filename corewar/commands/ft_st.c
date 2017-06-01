/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:25:18 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/01 17:31:06 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_st_1(t_corewar *data, t_carriage *src)
{
	ft_take_arg(data, src, 0, data->field[src->position + 1]);
	if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
	{
		src->arg[2] = src->position - 5 + (src->arg[2] % IDX_MOD);
		data->field[ft_fix(src->arg[2])] = (unsigned char)
			(src->reg[src->arg[1]] >> 24);
		data->field[ft_fix(src->arg[2]) + 1] = (unsigned char)
			(src->reg[src->arg[1]] >> 16);
		data->field[ft_fix(src->arg[2]) + 2] = (unsigned char)
			(src->reg[src->arg[1]] >> 8);
		data->field[ft_fix(src->arg[2]) + 3] = (unsigned char)
			(src->reg[src->arg[1]]);
		ft_write_meta(data, src->name, src->arg[2]);
	}
}

void	ft_st(t_corewar *data, t_carriage *src)
{
	if (data->field[src->position + 1] == 112)
		ft_st_1(data, src);
	else if (data->field[src->position + 1] == 80)
	{
		ft_take_arg(data, src, 0, data->field[src->position + 1]);
		if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0
			&& src->arg[2] <= REG_NUMBER)
			src->reg[src->arg[2]] = src->reg[src->arg[1]];
	}
	else
		ft_inc_index(src);
	ft_bzero(src->arg, 16);
}
