/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 12:45:47 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/01 16:45:52 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_fork(t_corewar *data, t_carriage *src)
{
	t_carriage *point;

	ft_inc_index(src);
	src->arg[1] = (short)((unsigned char)data->field[ft_inc_index(src)]
		<< 8) | (unsigned char)data->field[ft_inc_index(src)];
	point = data->carriage;
	while (point->next)
		point = point->next;
	src->arg[1] = ft_fix((src->position - 3) + (src->arg[1] % IDX_MOD));
	point->next = ft_create_carriage(src->arg[1], src->name, src);
	ft_bzero(src->arg, 16);
}
