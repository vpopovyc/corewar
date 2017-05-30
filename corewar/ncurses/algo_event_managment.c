/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:31:02 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/29 16:56:19 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualisation.h"

void	*crg_finder(void *arg)
{
	t_carriage			*crg;
	void	 			*ret;
	unsigned int 		i;

	crg = (t_carriage*)arg;
	i = crg->i;
	ret = (void*)malloc(sizeof(void));
	*((char*)ret) = 0;
	while (crg)
	{
		if (crg->position == i)
			*((char*)ret) = 1;
		crg = crg->next;
	}
	pthread_exit(ret);
}

void	turn_on_color(WINDOW *field, int i, char *mdata, t_carriage *crg)
{
	char 		player;
	void		*is_carrige;
	int			color_pair;
	pthread_t 	finder;

	color_pair = 0;
	crg->i = i;
	is_carrige = 0;
	player = mdata[i];
	pthread_create(&finder, &g_atr, crg_finder, crg);
	if (player == -1)
		color_pair |= P1RB;
	else if (player == -2)
		color_pair |= P2GB;
	else if (player == -3)
		color_pair |= P3YB;
	else if (player == -4)
		color_pair |= P4BB;
	pthread_join(finder, &is_carrige);
	if (*((char*)is_carrige))
		color_pair |= P0WW;
	wattron(field, COLOR_PAIR(color_pair));
	crg->i = color_pair;
	free(is_carrige);
}

void	turn_off_color(WINDOW *field, int color_pair)
{
	wattroff(field, COLOR_PAIR(color_pair));
}

void 	algo_event_managment(void)
{
	pthread_mutex_lock(&g_mutex_flag);
	if (g_flag & A_STOP)
	{
		pthread_mutex_unlock(&g_mutex_flag);
		while (1)
		{
			usleep (1 * 100000);
			pthread_mutex_lock(&g_mutex_flag);
			if (g_flag & EXIT)
				break ;
			if (!(g_flag & A_STOP))
				break ;
			pthread_mutex_unlock(&g_mutex_flag);
			usleep (4 * 100000);
		}
	}
	else if (g_flag & I_ERR)
	{
		pthread_mutex_unlock(&g_mutex_flag);
		while (1)
		{
			usleep (1 * 100000);
			pthread_mutex_lock(&g_mutex_flag);
			if (g_flag & EXIT)
				break ;
			if (!(g_flag & I_ERR))
				break ;
			pthread_mutex_unlock(&g_mutex_flag);
			usleep (4 * 100000);
		}
	}
	pthread_mutex_unlock(&g_mutex_flag);
}
