/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:04:15 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/01 13:04:18 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_live(t_corewar *data, t_carriage *src)
{
	ft_inc_index(src);
	src->arg[1] = (data->field[ft_inc_index(src)] << 24) |
		(data->field[ft_inc_index(src)] << 16) | (data->field[
		ft_inc_index(src)] << 8) | (data->field[ft_inc_index(src)]);
	if (-src->arg[1] >= 1 && -src->arg[1] <= data->count_ply)
	{
		data->players_live[-src->arg[1] - 1]++;
		src->live_in_cycle++;
	   	data->winer = src->arg[1];
	}
	src->live_in_cycle++;
	ft_bzero(src->arg, 16);
}
