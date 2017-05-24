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


#include <ncurses.h>
#include <unistd.h>

#define BOTTOM_WINDOW_HEIGHT	10
#define RIGHT_WINDOW_WIDTH		10

void	draw_borders(WINDOW *screen)
{
	attron(A_ALTCHARSET);
	wborder(screen, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	attroff(A_ALTCHARSET);
}

int main(int argc, char *argv[])
{
	int parent_x, parent_y, new_x, new_y;
	int bottom_size = BOTTOM_WINDOW_HEIGHT;
	int right_size = RIGHT_WINDOW_WIDTH;

	initscr();
	noecho();
	start_color();
	nodelay(stdscr, TRUE);
	curs_set(FALSE);

  	// set up initial windows
  	getmaxyx(stdscr, parent_y, parent_x);

  	bottom_size = (int)(parent_y / 4);
  	right_size = (int)(parent_x / 4);

  	WINDOW *field = newwin(parent_y - bottom_size, parent_x - right_size, 0, 0);
  	WINDOW *score = newwin(bottom_size, parent_x - right_size, parent_y - bottom_size, 0);
  	WINDOW *right = newwin(parent_y, right_size, 0, parent_x - right_size);

  	draw_borders(field);
  	draw_borders(score);
  	draw_borders(right);

  	while(1)
  	{
  		if (getch() == 'q')
  			break ;
  		else
  		{
	  		getmaxyx(stdscr, new_y, new_x);
	  		if (new_y != parent_y || new_x != parent_x)
	  		{
	  			parent_x = new_x;
	      		parent_y = new_y;
	      		wresize(field, new_y - bottom_size, new_x - right_size);
	      		wresize(score, bottom_size, new_x - right_size);
	      		wresize(right, new_y, right_size);
	      		mvwin(score, new_y - bottom_size, 0);
	      		mvwin(right, 0, new_x - right_size);
	      		wclear(stdscr);
	      		wclear(field);
	      		wclear(score);
	      		wclear(right);
	   		}
	   		init_pair(1, COLOR_BLACK, COLOR_WHITE);
	   		wbkgd(field, COLOR_PAIR(1));
      		draw_borders(field);
		    draw_borders(score);
		    draw_borders(right);
	    // draw to our windows
	   		if (new_y - bottom_size < 64 || new_x - right_size < 64)
	   		{
	      		wclear(stdscr);
	   			mvwprintw(stdscr, 10, 10, "Resize, please");
	   			wrefresh(stdscr);
	   		}
	   		else
	   		{
	   			mvwprintw(field, 1, 1, "Field");
		    	mvwprintw(score, 1, 1, "Score");
		    	mvwprintw(right, 1, 1, "Right");
		    // refresh each window
		    	wrefresh(field);
		    	wrefresh(score);
		    	wrefresh(right);
		    }
		}
  	}
  endwin();
  return 0;
}