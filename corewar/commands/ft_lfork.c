/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:01:17 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/02 12:23:58 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_lfork(t_corewar *data, t_carriage *src)
{
	t_carriage *new;

	ft_inc_index(src);
	src->arg[1] = (short)((unsigned char)data->field[ft_inc_index(src)] <<
		8) | (unsigned char)data->field[ft_inc_index(src)];
	src->arg[1] = ft_fix(src->position + src->arg[1]);
	new = ft_create_carriage(src->arg[1], src->reg[1], src, src->name_p);
	data->n_processes++;
	new->next = data->carriage;
	data->carriage = new;
	ft_bzero(src->arg, 16);
}
