/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_event_managment_addition.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 16:29:57 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/06/02 17:45:57 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualisation.h"

void	extend_key_event(char c)
{
	if (c == '1')
	{
		pthread_mutex_lock(&g_mutex_sec);
		g_sec = 10;
		pthread_mutex_unlock(&g_mutex_sec);
	}
	if (c == '2')
	{
		pthread_mutex_lock(&g_mutex_sec);
		g_sec = 20;
		pthread_mutex_unlock(&g_mutex_sec);
	}
	if (c == '3')
	{
		pthread_mutex_lock(&g_mutex_sec);
		g_sec = 30;
		pthread_mutex_unlock(&g_mutex_sec);
	}
	if (c == '4')
	{
		pthread_mutex_lock(&g_mutex_sec);
		g_sec = 40;
		pthread_mutex_unlock(&g_mutex_sec);
	}
}

void	extend_key_event_2(char c)
{
	if (c == 'p')
	{
		pthread_mutex_lock(&g_mutex_flag);
		g_mus ^= P_MUS;
		pthread_mutex_unlock(&g_mutex_flag);
	}
	if (c == ' ')
	{
		pthread_mutex_lock(&g_mutex_flag);
		g_flag ^= A_STOP;
		pthread_mutex_unlock(&g_mutex_flag);
	}
	if (c == '-')
	{
		pthread_mutex_lock(&g_mutex_sec);
		g_sec = g_sec == 0 ? 0 : g_sec - 1;
		pthread_mutex_unlock(&g_mutex_sec);
	}
	if (c == '+')
	{
		pthread_mutex_lock(&g_mutex_sec);
		g_sec = g_sec == 200 ? 200 : g_sec + 1;
		pthread_mutex_unlock(&g_mutex_sec);
	}
}

void	check_resize(t_init_screen *init)
{
	int y;
	int x;

	getmaxyx(stdscr, y, x);
	wattron(stdscr, A_ALTCHARSET);
	mvwprintw(stdscr, 0, 1, "%c%c%c%c",
	ACS_HLINE, ACS_HLINE, ACS_HLINE, ACS_HLINE);
	wattroff(stdscr, A_ALTCHARSET);
	if (y != init->parent_y || x != init->parent_x)
	{
		new_size_calc(init, y, x);
		if (!(g_flag & I_ERR))
		{
			resize_screens(init);
			draw_borders(init);
		}
	}
}

void	resize(void)
{
	wclear(stdscr);
	mvwprintw(stdscr, 1, 0, "Resize, please");
	wrefresh(stdscr);
	pthread_mutex_lock(&g_mutex_flag);
	g_flag |= I_ERR;
	g_mus |= P_MUS;
	pthread_mutex_unlock(&g_mutex_flag);
}

void	stop(char *tmp_flag, t_init_screen *init)
{
	*tmp_flag = g_sec | g_mus;
	pthread_mutex_unlock(&g_mutex_flag);
	while (1)
	{
		usleep(3 * 100000);
		pthread_mutex_lock(&g_mutex_sec);
		if (*tmp_flag != (g_sec | g_mus))
		{
			update_while_paused(init);
			*tmp_flag = g_sec | g_mus;
		}
		pthread_mutex_unlock(&g_mutex_sec);
		pthread_mutex_lock(&g_mutex_flag);
		if ((g_flag & EXIT) || (!(g_flag & A_STOP)))
			break ;
		pthread_mutex_unlock(&g_mutex_flag);
		usleep(3 * 100000);
	}
}
