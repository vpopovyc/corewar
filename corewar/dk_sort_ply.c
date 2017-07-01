/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dk_sort_ply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 16:24:11 by dkosolap          #+#    #+#             */
/*   Updated: 2017/05/29 18:07:44 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			find_nbr_ply(t_player *ply, int nbr)
{
	while (ply)
	{
		if (ply->number == nbr)
			return (0);
		ply = ply->next;
	}
	return (1);
}

void		add_nbr_ply(t_player *ply, int nbr, int max)
{
	while (ply)
	{
		if (ply->number > max)
			ft_error(6);
		if (!ply->number)
		{
			ply->number = nbr;
			return ;
		}
		ply = ply->next;
	}
}

void		add_ply_back(t_player **ply, t_player *tmp)
{
	t_player	*new;

	new = (t_player *)malloc(sizeof(t_player));
	new->name = tmp->name;
	new->comment = tmp->comment;
	new->code = tmp->code;
	new->number = tmp->number;
	new->size = tmp->size;
	new->next = NULL;
	tmp = *ply;
	if (!tmp)
	{
		*ply = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void		dk_free_ply(t_player **ply)
{
	if ((*ply)->next)
		dk_free_ply(&(*ply)->next);
	free(*ply);
}

void		dk_sort_ply(t_player **ply, int nbr)
{
	t_player	*tmp;
	t_player	*new;
	int			i;

	i = 0;
	while (++i <= nbr)
		if (find_nbr_ply(*ply, i))
			add_nbr_ply(*ply, i, nbr);
	i = 0;
	new = NULL;
	while (++i <= nbr)
	{
		tmp = *ply;
		while (tmp->number != i)
			tmp = tmp->next;
		add_ply_back(&new, tmp);
	}
	dk_free_ply(ply);
	*ply = new;
}
