/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:30:23 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/29 17:08:55 by rvolovik         ###   ########.fr       */
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
	if (bottom_size >= DES_BOT_S && panel_size >= DES_PANEL_S)
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
		mvwprintw(stdscr, 0, 1, "[2017]");
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
		if (c == 32)
			g_flag ^= 0x10;
		usleep(3 * 100000);
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

char	*get_color(WINDOW *bottom, int i)
{
	if (i == 3)
	{
		wattron(bottom, COLOR_PAIR(P1RB));
		return (COL_RED);
	}
	else if (i == 5)
	{
		wattron(bottom, COLOR_PAIR(P2GB));
		return (COL_GREEN);
	}
	else if (i == 7)
	{
		wattron(bottom, COLOR_PAIR(P3YB));
		return (COL_YELLOW);
	}
	else
	{
		wattron(bottom, COLOR_PAIR(P4BB));
		return (COL_BLUE);
	}
}

void 	unset_color(WINDOW *bottom, int i)
{
	if (i == 3)
		wattroff(bottom, COLOR_PAIR(P1RB));
	else if (i == 5)
		wattroff(bottom, COLOR_PAIR(P2GB));
	else if (i == 7)
		wattroff(bottom, COLOR_PAIR(P3YB));
	else if (i == 9)
		wattroff(bottom, COLOR_PAIR(P4BB));
}

void	print_usage(WINDOW *bottom)
{
	int y;

	y = 1;
	mvwprintw(bottom, y, 42, "Usage:");
	y += 2;
	mvwprintw(bottom, y, 44, "Best shapes is [77][245]");
	y += 2;
	mvwprintw(bottom, y, 44, "Use 'q' to quit");
	y += 2;
	mvwprintw(bottom, y, 44, "Use 'p' to pause music");
	y += 2;
	mvwprintw(bottom, y, 44, "Use 'space' to execute");
}

void	print_status(WINDOW *bottom)
{
	int 	y;
	int 	t_y;
	int 	t_x;

	y = 1;
	mvwprintw(bottom, y, 84, "Status:");
	y += 2;
	getmaxyx(stdscr, t_y, t_x);
	mvwprintw(bottom, y, 86, "Current shapes [%d][%d]", t_y, t_x);
	y += 2;
	if ((g_flag & R_CHK) == R_MUS)
		mvwprintw(bottom, y, 86, "Music is currently playing");
	else
		mvwprintw(bottom, y, 86, "Music is paused           ");
	y += 2;
	mvwprintw(bottom, y, 86, "INGA MAUER - MY FLIGHTS WITHOUT YOU");
	// y += 2;
	// mvwprintw(bottom, y, 86, "Something");
}

void	print_credits(WINDOW *bottom)
{
	int y;

	y = 1;
	mvwprintw(bottom, y, 126, "Team name: moshonka_yagnenka");
	y += 2;
	mvwprintw(bottom, y, 128, "Team-lead:                     vpopovyc");
	y += 2;
	mvwprintw(bottom, y, 128, "Ternary master:                mkrutik");
	y += 2;
	mvwprintw(bottom, y, 128, "Towerfall gamer:               dkosolap");
	y += 2;
	mvwprintw(bottom, y, 128, "The guy who came at the end:   rvolovik");
}

void	fill_bottom(WINDOW *bottom, t_player *ply, int num_ply)
{
	t_player 	*player;
	int 		y;
	int 		x;

	player = ply;
	y = 1;
	if (num_ply == 1)
		mvwprintw(bottom, y, 1, "There is 1 player :(", num_ply);
	else
		mvwprintw(bottom, y, 1, "There is %d players:", num_ply);
	while (player)
	{
		y += 2;
		mvwprintw(bottom, y, 1, "  %-15s - ", player->name);
		getyx(bottom, y, x);
		mvwprintw(bottom, y, x, "%s", get_color(bottom, y));
		unset_color(bottom, y);

		player = player->next;
	}
	print_usage(bottom);
	print_status(bottom);
	print_credits(bottom);
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

void	print_player_info(WINDOW *panel, t_corewar *src, int *y)
{
	t_player	*players;
	int			i;

	i = 3;
	players = src->players;
	wattron(panel, A_BOLD);
	while (players)
	{
		(*y) += 4;
		mvwprintw(panel, (*y), 3, "Player %d : ", i / 2);
		get_color(panel, i);
		mvwprintw(panel, (*y), 15, "%s", players->name);
		unset_color(panel, i);
		mvwprintw(panel, (*y) + 2, 15, "Lives summary : %d", src->players_live[i / 2 - 1]);
		i += 2;
		players = players->next;
	}
	wattroff(panel, A_BOLD);
}

void	fill_panel(WINDOW *panel, t_corewar *src)
{
	int		y;

	y = 2;
	wattron(panel, A_BOLD);
	if (!(g_flag & A_STOP))
		mvwprintw(panel, y, 3, "PLAYING");
	else
		mvwprintw(panel, y, 3, "PAUSED  ");
	y += 2;
	mvwprintw(panel, y, 3, "CYCLE_NUMBER : %d", src->curent_cycle);
	y += 2;
	mvwprintw(panel, y, 3, "COUNT_TO_CYCLE_TO_DIE : %d", src->last_cycle_to_die);
	y += 2;
	mvwprintw(panel, y, 3, "CYCLE_TO_DIE : %d", src->cycle_to_die);
	y += 2;
	mvwprintw(panel, y, 3, "NUMBER_CHECKS : %d", src->n_check);
	wattroff(panel, A_BOLD);
	print_player_info(panel, src, &y);
}

void	fill_screen(t_init_screen *init, t_corewar *src)
{
	fill_field(FIELD, src->game_field, src->meta_data, src->carriage);
	fill_bottom(BOTTOM, src->players, src->count_ply);
	fill_panel(PANEL, src);
	wrefresh(stdscr);
	wrefresh(FIELD);
	wrefresh(BOTTOM);
	wrefresh(PANEL);
}

void 	algo_event_managment()
{
	if (g_flag & A_STOP)
	{
		g_flag |= P_MUS;
		while (1)
		{
			if (g_flag & EXIT)
				break ;
			if (!(g_flag & A_STOP))
			{
				g_flag ^= P_MUS;
				break ;
			}
			usleep (5 * 100000);
		}
	}
	else if (g_flag & I_ERR)
	{
		while (1)
		{
			if (g_flag & EXIT)
				break ;
			if (!(g_flag & I_ERR))
				break ;
			usleep (5 * 100000);
		}
	}
}

int 	main(void)
{
	t_init_screen 	*init;
	/* tmp */
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
	src->players = (t_player*)ft_memalloc(sizeof(t_player));
	src->players->next = (t_player*)ft_memalloc(sizeof(t_player));
	src->players->next->next = (t_player*)ft_memalloc(sizeof(t_player));
	src->players->next->next->next = (t_player*)ft_memalloc(sizeof(t_player));
	src->players->name = strdup("Zork");
	src->players->next->name = strdup("Fluterrshy");
	src->players->next->next->name = strdup("Helltrain");
	src->players->next->next->next->name = strdup("Bigzork");
	src->curent_cycle = 0;
	src->cycle_to_die = 1500;
	src->last_cycle_to_die = 0;
	src->count_ply = 4;
	src->players_live = (int*)malloc(sizeof(int) * 4);
	src->players_live[0] = 5;
	src->players_live[1] = 4;
	src->players_live[2] = 3;
	src->players_live[3] = 2;
	/* tmp */
	init = init_ncurses();

	while (1)
	{
		if (g_flag & EXIT)
			break ;
		fill_screen(init, src);
		algo_event_managment();
		usleep (5 * 100000);
	}
	end_ncurses(init);
	return (0);
}
