/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:30:23 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/06/01 13:08:02 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualisation.h"

pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex_flag = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex_sec = PTHREAD_MUTEX_INITIALIZER;
pthread_t 		g_resize;
pthread_attr_t 	g_atr;
char			g_flag = A_STOP;
char 			g_mus = P_MUS;
int 			g_sec = 1;
pthread_t 		g_music;
pthread_t 		g_key;

void	resize_screens(t_init_screen *init)
{
	wclear(stdscr);
	wclear(FIELD);
	wclear(BOTTOM);
	wclear(PANEL);
	wresize(FIELD, init->field_y, init->field_x);
	wresize(BOTTOM, init->bottom_size, init->field_x);
	wresize(PANEL, init->parent_y, init->panel_size);
	mvwin(BOTTOM, init->field_y, 0);
	mvwin(PANEL, 0, init->field_x);
}

void	*size_controll(void *arg)
{
	t_init_screen 	*init;
	int 			y;
	int 			x;

	init = (t_init_screen*)arg;
	while (1)
	{
		pthread_mutex_lock(&g_mutex_flag);
		if (g_flag & EXIT)
		{
			pthread_mutex_unlock(&g_mutex_flag);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&g_mutex_flag);
		pthread_mutex_lock(&g_lock);
		getmaxyx(stdscr, y, x);
		wattron(stdscr, A_ALTCHARSET);
		mvwprintw(stdscr, 0, 1, "%c%c%c%c", ACS_HLINE, ACS_HLINE, ACS_HLINE, ACS_HLINE);
		wattroff(stdscr, A_ALTCHARSET);
		if (y != init->parent_y || x != init->parent_x)
		{
			new_size_calc(init, y, x);
			if (!(g_flag & I_ERR)) // no err – draw border
			{
				resize_screens(init);
				draw_borders(init);
			}
		}
		pthread_mutex_unlock(&g_lock);
		usleep(1 * 100000);
	}
}

void	*key_event(void *arg)
{
	char c;

	c = 0;
	(void)arg;
	while (1)
	{
		c = getch();
		if (c == 'q')
		{
			pthread_mutex_lock(&g_mutex_flag);
			g_flag |= EXIT;
			pthread_mutex_unlock(&g_mutex_flag);
			break ;
		}
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
			g_sec = g_sec == 1 ? 1 : g_sec - 1;
			pthread_mutex_unlock(&g_mutex_sec);
		}
		if (c == '+')
		{
			pthread_mutex_lock(&g_mutex_sec);
			g_sec = g_sec == 15 ? 15 : g_sec + 1;
			pthread_mutex_unlock(&g_mutex_sec);
		}
		usleep(2 * 100000);
	}
	pthread_exit(NULL);
}

t_init_screen 	*init_ncurses(void)
{
	t_init_screen 	*init;

	init = (t_init_screen*)ft_memalloc(sizeof(t_init_screen));
	initscr();
	noecho();
	start_color();
	init_color_pairs();
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	init_screens(init);
	/*
	** thread that control's resize
	*/
	pthread_attr_init(&g_atr);
	pthread_create(&g_resize, &g_atr, size_controll, init);
	pthread_detach(g_resize);
	/*
	** music
	*/
	pthread_create(&g_music, &g_atr, sound, &TRACK);
	pthread_detach(g_music);
	/*
	** key event
	*/
	pthread_create(&g_key, &g_atr, key_event, NULL);
	pthread_detach(g_key);
	return (init);
}

void	end_ncurses(t_init_screen *init, t_corewar *src)
{
	fill_screen(init, src);
	mvwprintw(BOTTOM, 9, 86, "Winner is %c", src->winer);
	wattron(PANEL, A_BOLD);
	mvwprintw(PANEL, 2, 3, "Press any key to exit", src->winer);
	wrefresh(BOTTOM);
	wrefresh(PANEL);
	wattroff(PANEL, A_BOLD);
	nodelay(stdscr, FALSE);
	getch();
	free(init);
	pthread_mutex_destroy(&g_lock);
	pthread_mutex_destroy(&g_mutex_flag);
	pthread_mutex_destroy(&g_mutex_sec);
	endwin();
}
