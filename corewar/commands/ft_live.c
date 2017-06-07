/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:04:15 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/06 19:06:03 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"


void	ft_rename(t_corewar *data, t_carriage *src, int name)
{
	t_player	*p;
	int			i;

	p = data->players;
	i = 1;
	while (p)
	{
		if (i == name)
		{
			src->name = -i;
			src->name_p = p->name;
		}
		p = p->next;
		i++;
	}
}

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
		if (src->name != src->arg[1])
			ft_rename(data, src, -src->arg[1]);
		data->winer = src->name_p;
		data->n_winer = src->name;
		if (data->verbose != 1)
		{
			ft_printf("A process shows that player %d", (int)src->name);
			ft_printf(" (%s) is alive\n", src->name_p);
		}
	}
	ft_bzero(src->arg, 16);
}
