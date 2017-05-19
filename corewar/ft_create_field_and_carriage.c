/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_field_and_carriage.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 12:33:16 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/19 12:34:16 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_carriage	*ft_create_carriage(unsigned int posinion)
{
	t_carriage *new;

	new = (t_carriage*)malloc(sizeof(t_carriage));
	new->count_live = 0;
	new->cycle = 0;
	new->last_live = 0;
	new->posinion = posinion;
	new->next = NULL;
	return (new);
}

void		ft_count_free_mem_size(t_player *head, int *free_space)
{
	t_player	*point;
	int			sum_size;
	int			n_player;

	sum_size = 0;
	n_player = 0;
	point = head;
	while (point)
	{
		sum_size += point->size;
		n_player++;
		point = point->next;
	}
	*free_space = (MEM_SIZE - sum_size) / n_player;
}

void		ft_create_field_and_carriage(t_corewar *src, int free_space, int n)
{
	t_player		*point;
	char			*p;
	t_carriage		*carriage;

	src->game_field = ft_strnew(MEM_SIZE - 1);
	src->carriage = ft_create_carriage(0);
	ft_count_free_mem_size(src->players, &free_space);
	carriage = src->carriage;
	point = src->players;
	p = src->game_field;
	while (point)
	{
		if (n == 0)
			ft_memcpy(p, point->code, point->size);
		else
		{
			carriage->next = ft_create_carriage(n);
			carriage = carriage->next;
			ft_memcpy(p + n, point->code, point->size);
		}
		n += point->size + free_space;
		point = point->next;
	}
}
