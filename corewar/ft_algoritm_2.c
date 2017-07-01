/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algoritm_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 12:25:30 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/06 18:45:33 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_algoritm(t_corewar *src)
{
	while (src->carriage && src->cycle_to_die != 0 && src->fdump !=
			(int)src->curent_cycle)
	{
		ft_check_mem_cell(src->carriage, src->field);
		if (((int)src->last_cycle_to_die + 1) == (int)src->cycle_to_die)
		{
			src->carriage = ft_check_del_carriege(src, src->carriage);
			ft_check_cycle_to_die(src, 0, 0);
		}
		else
			src->last_cycle_to_die++;
		ft_increment_cycle(src, src->carriage);
		sub_meta_bold(src->meta_bold);
		src->curent_cycle++;
	}
	(src->fdump != -1 && src->fdump == (int)src->curent_cycle) ?
	dk_dump(src->field) :
	ft_printf("\x1b[32mPlayer %d (%s) won\n\x1b[0m", src->n_winer, src->winer);
}
