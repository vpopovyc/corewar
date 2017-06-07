/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algoritm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:45:23 by dkosolap          #+#    #+#             */
/*   Updated: 2017/06/07 18:06:19 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ncurses/visualisation.h"

void		ft_check_cycle_to_die(t_corewar *src, int n_live, int i)
{
	t_carriage	*p;

	p = src->carriage;
	while (p)
	{
		p->live_in_cycle = 0;
		p = p->next;
	}
	while (i < src->count_ply)
	{
		(src->players_live[i] >= n_live) ? (n_live = src->players_live[i]) : 0;
		i++;
	}
	if (n_live >= NBR_LIVE || src->n_check == MAX_CHECKS)
	{
		src->n_check = 0;
		src->cycle_to_die = (src->cycle_to_die < CYCLE_DELTA) ? 0 :
			(src->cycle_to_die - CYCLE_DELTA);
	}
	else
		src->n_check++;
	ft_bzero(src->players_live, 4 * src->count_ply);
	src->last_cycle_to_die = 0;
}

void		ft_check_mem_cell(t_carriage *head, char *field)
{
	t_carriage	*tmp;

	tmp = head;
	while (tmp)
	{
		if ((unsigned char)field[tmp->position] > 0 &&
				(unsigned char)field[tmp->position] <= 16)
		{
			if (!tmp->f)
			{
				tmp->f = g_funcs[field[tmp->position] - 1];
				tmp->comand_cycle = g_op[field[tmp->position] - 1].cycles;
				if (field[tmp->position] == 1)
					tmp->live_in_cycle++;
			}
		}
		else
			tmp->position = ((tmp->position - 1) != MEM_SIZE) ?
				(tmp->position + 1) : 0;
		tmp = tmp->next;
	}
}

void		ft_increment_cycle(t_corewar *src, t_carriage *head)
{
	t_carriage	*point;

	point = head;
	while (point)
	{
		if (point->f)
			point->comand_cycle--;
		if (point->comand_cycle == 0 && point->f)
		{
			point->f(src, point);
			point->f = NULL;
			point->comand_cycle = 0;
		}
		point = point->next;
	}
}

void		sub_meta_bold(char *src)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (src[i])
			src[i]--;
	}
}

void		ft_algoritm_visual(t_corewar *src, t_init_screen *init)
{
	init = init_ncurses();
	while (src->carriage && src->cycle_to_die != 0 && src->fdump !=
			(int)src->curent_cycle)
	{
		pthread_mutex_lock(&g_mutex_flag);
		if (g_flag & EXIT)
			break ;
		pthread_mutex_unlock(&g_mutex_flag);
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
		g_car = src->n_processes;
		fill_screen(init, src);
		algo_event_managment(init);
	}
	end_ncurses(init, src);
}
