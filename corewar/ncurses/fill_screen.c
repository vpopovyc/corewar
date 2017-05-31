/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:31:02 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/31 12:30:33 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualisation.h"

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
	pthread_mutex_lock(&g_mutex_flag);
	if (!(g_flag & A_STOP))
		mvwprintw(panel, y, 3, "PLAYING");
	else
		mvwprintw(panel, y, 3, "PAUSED  ");
	pthread_mutex_unlock(&g_mutex_flag);
	y += 2;
	mvwprintw(panel, y, 3, "Cycles/second limit : %d", g_sec);
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

void	fill_screen(t_init_screen *init, t_corewar *src)
{
	if (!(g_flag & I_ERR))
	{
		pthread_mutex_lock(&g_lock);
		fill_field(FIELD, src->game_field, src->meta_data, src->carriage);
		fill_bottom(BOTTOM, src->players, src->count_ply);
		fill_panel(PANEL, src);
		wrefresh(stdscr);
		wrefresh(FIELD);
		wrefresh(BOTTOM);
		wrefresh(PANEL);
		pthread_mutex_unlock(&g_lock);
	}
}
