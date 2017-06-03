/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:30:23 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/06/02 19:11:38 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualisation.h"

pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex_flag = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex_sec = PTHREAD_MUTEX_INITIALIZER;
pthread_t		g_resize;
pthread_attr_t	g_atr;
char			g_flag = A_STOP;
char			g_mus = P_MUS;
int				g_sec = 30;
int				g_car = 0;
pthread_t		g_music;
pthread_t		g_key;

void			resize_screens(t_init_screen *init)
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

void			*size_controll(void *arg)
{
	t_init_screen	*init;

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
		check_resize(init);
		pthread_mutex_unlock(&g_lock);
		usleep(8 * 100000);
	}
}

void			*key_event(void *arg)
{
	char c;

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
		extend_key_event(c);
		extend_key_event_2(c);
		usleep(2 * 100000);
	}
	pthread_exit(NULL);
}

t_init_screen	*init_ncurses(void)
{
	t_init_screen	*init;

	init = (t_init_screen*)ft_memalloc(sizeof(t_init_screen));
	initscr();
	noecho();
	start_color();
	init_color_pairs();
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	init_screens(init);
	pthread_attr_init(&g_atr);
	pthread_create(&g_resize, &g_atr, size_controll, init);
	pthread_detach(g_resize);
	pthread_create(&g_music, &g_atr, sound, &TRACK);
	pthread_detach(g_music);
	pthread_create(&g_key, &g_atr, key_event, NULL);
	pthread_detach(g_key);
	return (init);
}

void			end_ncurses(t_init_screen *init, t_corewar *src)
{
	mvwprintw(BOTTOM, 9, 86, "Winner is %s  ", src->winer);
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
