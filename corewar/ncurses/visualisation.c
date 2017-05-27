/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:30:23 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/24 19:30:26 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualisation.h"

pthread_mutex_t g_lock;
pthread_t 		g_resize;
pthread_attr_t 	g_atr;
char			g_flag;
pthread_t 		g_music;

void	draw_borders(t_init_screen *init)
{
	attron(A_ALTCHARSET);
	wborder(FIELD, ACS_VLINE, ACS_VLINE, ACS_HLINE, 
		ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	wborder(BOTTOM, ACS_VLINE, ACS_VLINE, ACS_HLINE, 
		ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	wborder(PANEL, ACS_VLINE, ACS_VLINE, ACS_HLINE, 
		ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	wrefresh(stdscr);
	wrefresh(FIELD);
	wrefresh(BOTTOM);
	wrefresh(PANEL);
	attroff(A_ALTCHARSET);
}

void	new_size_calc(t_init_screen *init, int new_y, int new_x)
{
	int 	bottom_size;
	int 	panel_size;
	int 	field_x;
	int 	field_y;

	init->parent_x = new_x;
	init->parent_y = new_y;
	
	bottom_size = new_y - DES_FIELD_Y;
	panel_size = new_x - DES_FIELD_X;
	field_y = DES_FIELD_Y;
	field_x = DES_FIELD_X;
	if (bottom_size >= 0 && panel_size >= 0)
	{
		init->bottom_size = bottom_size;
		init->panel_size = panel_size;
		init->field_x = field_x;
		init->field_y = field_y;
		if (g_flag & 0x2)
			g_flag ^= 0x6;
	}
	else
	{
		wclear(stdscr);
	   	mvwprintw(stdscr, 30, 30, "Resize, please");
	   	wrefresh(stdscr);
	   	g_flag |= 0x2;
	}
}

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

void	init_screens(t_init_screen *init)
{
	int 	y;
	int 	x;

	getmaxyx(stdscr, y, x);
	new_size_calc(init, y, x);
	FIELD = newwin(init->field_y, init->field_x, 0, 0);
	BOTTOM = newwin(init->bottom_size, init->field_x, init->field_y, 0);
	PANEL = newwin(y, init->panel_size, 0, init->field_x);
	draw_borders(init);
}

void	*size_controll(void *arg)
{
	t_init_screen 	*init;
	int 			y;
	int 			x;

	init = (t_init_screen*)arg;
	while (1)
	{
		if (g_flag & 0x1)
			pthread_exit(NULL);
		pthread_mutex_lock(&g_lock);
		getmaxyx(stdscr, y, x);
		mvwprintw(stdscr, 10, 10, "%d  %d", y, x);
		if (y != init->parent_y || x != init->parent_x)
		{
			new_size_calc(init, y, x);
			if (!(g_flag & 0x2))
			{
				resize_screens(init);
				draw_borders(init);
			}
		}
		pthread_mutex_unlock(&g_lock);
		usleep(5 * 100000);
	}
}

void	init_ncurses(void)
{
	t_init_screen 	init;

	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	init_screens(&init);
	/*
	** thread that control's resize
	*/
	pthread_mutex_init(&g_lock, NULL);
	pthread_attr_init(&g_atr);
	pthread_create(&g_resize, &g_atr, size_controll, &init);
	pthread_detach(g_resize);
	/* music */
	pthread_create(&g_music, &g_atr, sound, &TRACK);
	pthread_detach(g_music);

	char c;
	while (1)
	{
		c = getch();
		if (c == 'q')
			break ;
		if (c == 'i')
			g_flag = 1;
		usleep(5 * 100000);
	}
	pthread_mutex_destroy(&g_lock);
}

int 	main(void)
{
	init_ncurses();

	endwin();
	return (0);
}
