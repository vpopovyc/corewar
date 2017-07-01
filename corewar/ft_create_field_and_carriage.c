/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_field_and_carriage.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 12:40:21 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/06 19:34:19 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_carriage	*ft_check_del_carriege(t_corewar *data, t_carriage *src)
{
	t_carriage	*point;

	point = src;
	while (point)
	{
		if (point->live_in_cycle == 0)
		{
			src = ft_del_carriage(src, point);
			point = src;
			data->n_processes--;
		}
		else
			point = point->next;
	}
	return (src);
}

t_carriage	*ft_del_carriage(t_carriage *src, t_carriage *del)
{
	t_carriage		*head;
	t_carriage		*previous;

	if (del == src)
		head = src->next;
	else
	{
		head = src;
		previous = src;
		while (src != del)
		{
			previous = src;
			src = src->next;
		}
		previous->next = src->next;
	}
	free(src);
	return (head);
}

t_carriage	*ft_create_carriage(unsigned int posinion,
			int num, t_carriage *data, char *name)
{
	t_carriage *new;

	new = (t_carriage*)malloc(sizeof(t_carriage));
	new->comand_cycle = 0;
	new->f = NULL;
	new->live_in_cycle = 0;
	new->position = posinion;
	new->next = NULL;
	ft_bzero(new->reg, 4 * REG_NUMBER);
	if (data)
	{
		ft_memcpy(new->reg, data->reg, 4 * REG_NUMBER);
		new->carry = data->carry;
		new->name = (char)new->reg[1];
	}
	else
	{
		new->reg[1] = num;
		new->name = (char)num;
		new->carry = 0;
	}
	new->name_p = name;
	return (new);
}

void		dk_field_meta(char *meta, int name, int start, int len)
{
	int		i;

	i = -1;
	while (++i < len)
		meta[ft_fix(start + i)] = -name;
}

void		ft_create_field_and_carriage(t_corewar *src, int n,
			int num, char *p)
{
	t_player		*point;
	t_carriage		*carriage;

	src->carriage = ft_create_carriage(0, -1, NULL, src->players->name);
	src->carriage->reg[1] = -1;
	carriage = src->carriage;
	point = src->players;
	while (point)
	{
		if (n == 0)
			ft_memcpy(p, point->code, point->size);
		else
		{
			carriage->next = ft_create_carriage(n, num--, NULL, point->name);
			carriage = carriage->next;
			ft_memcpy(p + n, point->code, point->size);
		}
		src->n_processes++;
		dk_field_meta(src->meta_data, point->number, n, point->size);
		n += MEM_SIZE / src->count_ply;
		point = point->next;
	}
}
