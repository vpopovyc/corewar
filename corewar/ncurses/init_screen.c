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
		pthread_mutex_lock(&g_mutex_flag);
		if (g_flag & I_ERR)
		{
			g_flag ^= I_ERR;
			g_mus ^= P_MUS;
		} // err fixed – resume music && draw border
		pthread_mutex_unlock(&g_mutex_flag);
	}
	else
	{
		wclear(stdscr);
	   	mvwprintw(stdscr, 1, 0, "Resize, please");
	   	wrefresh(stdscr);
	   	pthread_mutex_lock(&g_mutex_flag);
	   	g_flag |= I_ERR; // get err – stop music && dont draw border
	   	g_mus |= P_MUS;
	   	pthread_mutex_unlock(&g_mutex_flag);
	}
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
   	pthread_mutex_lock(&g_mutex_flag);
	if (!(g_flag & I_ERR))
		draw_borders(init);
	pthread_mutex_unlock(&g_mutex_flag);
}
