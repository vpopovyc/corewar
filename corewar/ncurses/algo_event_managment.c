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

char	crg_finder(t_carriage *arg)
{
	t_carriage			*crg;
	unsigned int		i;

	crg = arg;
	if (crg)
	{
		i = crg->i;
		while (crg)
		{
			if (crg->position == i)
				return (1);
			crg = crg->next;
		}
	}
	return (0);
}

void	turn_on_color(WINDOW *field, int i, char *mdata, t_carriage *crg)
{
	char		player;
	char		is_carrige;
	int			color_pair;

	color_pair = 0;
	(crg) ? crg->i = i : 0;
	is_carrige = crg_finder(crg);
	player = mdata[i];
	if (player == 0)
		color_pair |= P0BB;
	else if (player == -1)
		color_pair |= P1RB;
	else if (player == -2)
		color_pair |= P2GB;
	else if (player == -3)
		color_pair |= P3YB;
	else if (player == -4)
		color_pair |= P4BB;
	if (is_carrige)
		color_pair |= P0WW;
	if (color_pair != P0BB && !g_meta_bold[i])
		wattron(field, COLOR_PAIR(color_pair));
	else
		wattron(field, COLOR_PAIR(color_pair) | A_BOLD);
	(crg) ? crg->i = color_pair : 0;
}

void	turn_off_color(WINDOW *field, t_carriage *crg, int i)
{
	int color_pair;

	if (crg)
		color_pair = crg->i;
	else
		color_pair = 0;
	if (color_pair == P0BB || (g_meta_bold && g_meta_bold[i]))
		wattroff(field, COLOR_PAIR(color_pair) | A_BOLD);
	else
		wattroff(field, COLOR_PAIR(color_pair));
}

void	update_while_paused(t_init_screen *init)
{
	pthread_mutex_lock(&g_lock);
	wattron(PANEL, A_BOLD);
	mvwprintw(PANEL, 4, 3, "Cycles/second limit : %d      ", g_sec);
	wattroff(PANEL, A_BOLD);
	if ((g_mus & R_CHK) == R_MUS)
		mvwprintw(BOTTOM, 5, 86, "Music is currently playing");
	else
		mvwprintw(BOTTOM, 5, 86, "Music is paused           ");
	wrefresh(PANEL);
	wrefresh(BOTTOM);
	wrefresh(FIELD);
	pthread_mutex_unlock(&g_lock);
}

void	algo_event_managment(t_init_screen *init)
{
	char tmp_flag;

	pthread_mutex_lock(&g_mutex_flag);
	if (g_flag & A_STOP)
		stop(&tmp_flag, init);
	else if (g_flag & I_ERR)
	{
		pthread_mutex_unlock(&g_mutex_flag);
		while (1)
		{
			usleep(3 * 100000);
			pthread_mutex_lock(&g_mutex_flag);
			if (g_flag & EXIT)
				break ;
			if (!(g_flag & I_ERR))
				break ;
			pthread_mutex_unlock(&g_mutex_flag);
			usleep(3 * 100000);
		}
	}
	pthread_mutex_unlock(&g_mutex_flag);
}
