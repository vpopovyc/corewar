/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:04:15 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/01 13:45:39 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_live(t_corewar *data, t_carriage *src)
{
	ft_inc_index(src);
	src->arg[1] = ((unsigned char)data->field[ft_inc_index(src)] << 24) |
		((unsigned char)data->field[ft_inc_index(src)] << 16)
		| ((unsigned char)data->field[ft_inc_index(src)] << 8)
		| ((unsigned char)data->field[ft_inc_index(src)]);
	if (-src->arg[1] >= 1 && -src->arg[1] <= data->count_ply)
	{
		data->players_live[-src->arg[1] - 1]++;
	   	data->winer = src->arg[1];
	}
	src->live_in_cycle++;
	ft_bzero(src->arg, 16);
}
