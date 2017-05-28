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
pthread_t 		g_key;

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
		if (g_flag & I_ERR) // err fixed – resume music && draw border
			g_flag ^= CLEAN;
	}
	else
	{
		wclear(stdscr);
	   	mvwprintw(stdscr, 1, 0, "Resize, please");
	   	wrefresh(stdscr);
	   	g_flag = g_flag | I_ERR | P_MUS; // get err – stop music && dont draw border
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

void	init_color_pairs(void)
{
	init_pair(P1RB, COLOR_RED, COLOR_BLACK);
	init_pair(P2GB, COLOR_GREEN, COLOR_BLACK);
	init_pair(P3YB, COLOR_YELLOW, COLOR_BLACK);
	init_pair(P4BB, COLOR_BLUE, COLOR_BLACK);
	init_pair(P1RW, COLOR_RED, COLOR_WHITE);
	init_pair(P2GW, COLOR_GREEN, COLOR_WHITE);
	init_pair(P3YW, COLOR_YELLOW, COLOR_WHITE);
	init_pair(P4BW, COLOR_BLUE, COLOR_WHITE);
	init_pair(P0WW, COLOR_WHITE, COLOR_WHITE);
}

void	*size_controll(void *arg)
{
	t_init_screen 	*init;
	int 			y;
	int 			x;

	init = (t_init_screen*)arg;
	while (1)
	{
		if (g_flag & EXIT)
			pthread_exit(NULL);
		pthread_mutex_lock(&g_lock);
		getmaxyx(stdscr, y, x);
		mvwprintw(stdscr, 0, 1, "[%d][%d]", y, x);
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
		usleep(5 * 100000);
	}
}

void	*key_event(void *arg)
{
	char c;

	c = 0;
	while (1)
	{
		c = getch();
		if (c == 'q')
		{
			g_flag |= 0x1;
			usleep(2 * 100000);
			break ;
		}
		if (c == 'p')
			g_flag ^= 0x4;
		usleep(1 * 100000);
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
	pthread_mutex_init(&g_lock, NULL);
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
	return (init);
}

void	end_ncurses(t_init_screen *init)
{
	pthread_join(g_key, NULL);
	pthread_mutex_destroy(&g_lock);
	free(init);
	endwin();
}

void	*crg_finder(void *arg)
{
	t_carriage	*crg;
	void	 	*ret;
	int 		i;

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

void	fill_field(WINDOW *field, char *gamefield, char *mdata, t_carriage *crg)
{
	int 	y;
	int 	x;
	int 	i;

	i = 0;
	y = 1;
	x = 2;
	while (y < DES_FIELD_Y)
	{
		x = 2;
		while (i < MEM_SIZE)
		{
			turn_on_color(field, i, mdata, crg);
			mvwprintw(field, y, x, "%.2hhx", gamefield[i]);
			turn_off_color(field, crg->i);
			++i;
			if ((i % 64) == 0)
				break ;
			x += 3;
		}
		++y;
	}
	wborder(field, ACS_VLINE, ACS_VLINE, ACS_HLINE, 
		ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
}

void	fill_screen(t_init_screen *init, t_corewar *src)
{
	wclear(FIELD);
	fill_field(FIELD, src->game_field, src->meta_data, src->carriage);
	wrefresh(stdscr);
	wrefresh(FIELD);
	wrefresh(BOTTOM);
	wrefresh(PANEL);
}

int 	main(void)
{
	t_init_screen 	*init;

/* tmp
*/
	t_corewar *src = (t_corewar*)ft_memalloc(sizeof(t_corewar));
	src->game_field = ft_strnew(MEM_SIZE - 1);
	src->meta_data = ft_strnew(MEM_SIZE - 1);
	src->meta_data[0] = -1;
	src->meta_data[1] = -2;
	src->meta_data[2] = -3;
	src->meta_data[3] = -4;
	src->meta_data[4] = -1;
	src->meta_data[5] = -2;
	src->meta_data[6] = -3;
	src->meta_data[7] = -4;
	ft_memset((void*)src->game_field, 0x42, MEM_SIZE / 2);
	ft_memset((void*)src->game_field + (MEM_SIZE / 2), 0x21, MEM_SIZE / 2);
	src->carriage = (t_carriage*)ft_memalloc(sizeof(t_carriage));
	src->carriage->next = (t_carriage*)ft_memalloc(sizeof(t_carriage));
	src->carriage->next->next = (t_carriage*)ft_memalloc(sizeof(t_carriage));
	src->carriage->next->next->next = (t_carriage*)ft_memalloc(sizeof(t_carriage));
	src->carriage->next->next->next->next = (t_carriage*)ft_memalloc(sizeof(t_carriage));
	src->carriage->position = 4;
	src->carriage->next->position = 5;
	src->carriage->next->next->position = 6;
	src->carriage->next->next->next->position = 7;
	src->carriage->next->next->next->next->position = 8; 
/* tmp
*/
	init = init_ncurses();

	fill_screen(init, src);

	end_ncurses(init);
	return (0);
}
