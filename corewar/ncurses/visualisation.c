/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:30:23 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/06/08 12:10:45 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualisation.h"

pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex_flag = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex_sec = PTHREAD_MUTEX_INITIALIZER;
pthread_attr_t	g_atr;
char			g_flag = A_STOP;
char			g_mus = P_MUS;
int				g_sec = 2;
int				g_car = 0;
pthread_t		g_music;
pthread_t		g_key;

void			*key_event(void *arg)
{
	int c;

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
	}
	pthread_exit(NULL);
}

t_init_screen	*init_ncurses(void)
{
	t_init_screen	*init;

	init = (t_init_screen*)ft_memalloc(sizeof(t_init_screen));
	ft_putstr(WINDOW_SETTINGS);
	usleep(5 * 100000);
	initscr();
	noecho();
	start_color();
	init_color_pairs();
	nodelay(stdscr, FALSE);
	curs_set(FALSE);
	init_screens(init);
	pthread_attr_init(&g_atr);
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
	wclear(stdscr);
	free(init);
	pthread_mutex_destroy(&g_lock);
	pthread_mutex_destroy(&g_mutex_flag);
	pthread_mutex_destroy(&g_mutex_sec);
	endwin();
}
