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
	}
	else
	{
		nodelay(stdscr, FALSE);
		wclear(stdscr);
	   	mvwprintw(stdscr, 10, 10, "Resize, please");
	   	wrefresh(stdscr);
	   	getch();
		nodelay(stdscr, TRUE);
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
		if (g_flag)
			pthread_exit(NULL);
		pthread_mutex_lock(&g_lock);
		getmaxyx(stdscr, y, x);
		mvwprintw(stdscr, 10, 10, "%d  %d", y, x);
		if (y != init->parent_y || x != init->parent_x)
		{
			new_size_calc(init, y, x);
			resize_screens(init);
			draw_borders(init);
		}
		pthread_mutex_unlock(&g_lock);

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
	// g_lock = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&g_lock, NULL);
	pthread_attr_init(&g_atr);
	pthread_create(&g_resize, &g_atr, size_controll, &init);
	pthread_detach(g_resize);

	char c;
	while (1)
	{
		c = getch();
		if (c == 'q')
			break ;
		if (c == 'i')
			g_flag = 1;
	}
	pthread_mutex_destroy(&g_lock);
}

int 	main(void)
{
	init_ncurses();

	endwin();
	return (0);
}

// int 	main(int argc, char *argv[])
// {
// 	int parent_x, parent_y, new_x, new_y;
// 	int bottom_size = BOTTOM_WINDOW_HEIGHT;
// 	int right_size = RIGHT_WINDOW_WIDTH;

// 	initscr();
// 	noecho();
// 	nodelay(stdscr, TRUE);
// 	curs_set(FALSE);

//   	// set up initial windows
//   	getmaxyx(stdscr, parent_y, parent_x);

//   	bottom_size = (int)(parent_y / 4);
//   	right_size = (int)(parent_x / 4);

//   	WINDOW *field = newwin(parent_y - bottom_size, parent_x - right_size, 0, 0);
//   	WINDOW *score = newwin(bottom_size, parent_x - right_size, parent_y - bottom_size, 0);
//   	WINDOW *right = newwin(parent_y, right_size, 0, parent_x - right_size);

  	// draw_borders(field);
  	// draw_borders(score);
  	// draw_borders(right);

//   	while(1)
//   	{
//   		if (getch() == 'q')
//   			break ;
//   		else
//   		{
// 	  		getmaxyx(stdscr, new_y, new_x);
// 	  		if (new_y != parent_y || new_x != parent_x)
// 	  		{
// 	  			parent_x = new_x;
// 	      		parent_y = new_y;
// 				bottom_size = (int)(parent_y / 4);
// 				right_size = (int)(parent_x / 4);
// 	      		wresize(field, new_y - bottom_size, new_x - right_size);
// 	      		wresize(score, bottom_size, new_x - right_size);
// 	      		wresize(right, new_y, right_size);
// 	      		mvwin(score, new_y - bottom_size, 0);
// 	      		mvwin(right, 0, new_x - right_size);
	      		// wclear(stdscr);
	      		// wclear(field);
	      		// wclear(score);
	      		// wclear(right);
// 	   		}
//       		draw_borders(field);
// 		    draw_borders(score);
// 		    draw_borders(right);
// 	    // draw to our windows
// 	   		if (new_y - bottom_size < 64 || new_x - right_size < 200)
// 	   		{
	      // 		wclear(stdscr);
	   			// mvwprintw(stdscr, 10, 10, "Resize, please");
	   			// wrefresh(stdscr);
// 	   		}
// 	   		else
// 	   		{
// 	   			mvwprintw(field, 1, 1, "Field");
// 		    	mvwprintw(score, 1, 1, "Score");
// 		    	mvwprintw(right, 1, 1, "Right");
// 		    // refresh each window
		    	// wrefresh(field);
		    	// wrefresh(score);
		    	// wrefresh(right);
// 		    }
// 		}
//   	}
//   endwin();
//   return 0;
// }