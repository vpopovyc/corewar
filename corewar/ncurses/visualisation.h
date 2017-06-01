/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:31:02 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/31 12:25:42 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VISUALISATION_H
# define __VISUALISATION_H

# include <ncurses.h>
# include <unistd.h>
# include <pthread.h>
# include "sounds/sounds.h"
# include "../corewar.h"

# define FIELD 	init->win[0]
# define BOTTOM	init->win[1]
# define PANEL 	init->win[2]

# define DES_FIELD_Y 66 // 64 + 2 ((MEM_SIZE / 64) + 2)
# define DES_FIELD_X 195 // 64 * 2 + 64 + 3
# define DES_BOT_S	 11
# define DES_PANEL_S 40

# define TRACK "ncurses/sounds/background.wav"

# define EXIT	0x1
# define I_ERR 	0x2
# define P_MUS	0x4 // play m
# define S_MUS	0x8 // stop m
# define R_MUS	0x8 // resume m
# define CLEAN	0x6
# define A_STOP	0x10 //pause processes
# define R_CHK	0xe // check if resume needed

/*
** color pairs
*/

# define P1RB 1 // RED_BLACK
# define P2GB 2 // GREEN_BLACK
# define P3YB 4 // YELLOW_BLACK
# define P4BB 8 // BLUE_BLACK 
# define P0WW 16 // WHITE_WHITE
# define P0BB 32 // BLACK_BLACK
# define P1RW 17 // RED_WHITE
# define P2GW 18 // GREEN_WHITE
# define P3YW 20 // YELLOW_WHITE
# define P4BW 24 // BLUE_WHITE
# define P0WB 48 // WHITE_BLACK
/*
** COLORS
*/

# define COL_RED 	"RED"
# define COL_GREEN	"GREEN"
# define COL_YELLOW	"YELLOW"
# define COL_BLUE	"BLUE"
# define COL_GRAY	0

typedef struct 	s_init_screen
{
	WINDOW 			*win[3];
	int 			parent_x;
	int 			parent_y;
	int 			field_x;
	int 			field_y;
	int 			bottom_size;
	int 			panel_size;
}				t_init_screen;

extern pthread_mutex_t 	g_lock;
extern pthread_mutex_t 	g_mutex_flag;
extern pthread_mutex_t g_mutex_sec;
extern pthread_t 		g_resize;
extern pthread_t 		g_music;
extern pthread_t 		g_key;
extern pthread_attr_t 	g_atr;
extern char				g_flag;
extern char				g_mus;
extern int				g_sec;

/*
** visualisation.c
*/

t_init_screen 	*init_ncurses(void);
void			end_ncurses(t_init_screen *init, t_corewar *src);
void			resize_screens(t_init_screen *init);

/*
** init_screen.c
*/

void	init_screens(t_init_screen *init);
void	new_size_calc(t_init_screen *init, int new_y, int new_x);
void	draw_borders(t_init_screen *init);
void	init_color_pairs(void);

/*
** fill_screen.c
*/

void	fill_screen(t_init_screen *init, t_corewar *src);

/*
** usage_status_credits.c
*/

void	print_usage(WINDOW *bottom);
void	print_status(WINDOW *bottom);
void	print_credits(WINDOW *bottom);
void 	unset_color(WINDOW *bottom, int i);
char	*get_color(WINDOW *bottom, int i);

/*
** algo_event_managment.c
*/

void 	algo_event_managment(t_init_screen *init);
void    turn_off_color(WINDOW *field, t_carriage *crg);
void	turn_on_color(WINDOW *field, int i, char *mdata, t_carriage *crg);

#endif


/*
    0   0  0  0  0 0 0 0
    128 64 32 16 8 4 2 1

a 	b 	c 	d 	e 	f
10	11	12	13	14	15

*/
