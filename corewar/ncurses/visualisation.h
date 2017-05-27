/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:31:02 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/24 19:31:04 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VISUALISATION_H
# define __VISUALISATION_H

# include <ncurses.h>
# include <unistd.h>
# include <pthread.h>
# include "sounds/sounds.h"
# include "../../op.h"
# include "../../libft/includes/libft.h"

# define FIELD 	init->win[0]
# define BOTTOM	init->win[1]
# define PANEL 	init->win[2]

# define DES_FIELD_Y 64
# define DES_FIELD_X 256

# define TRACK "sounds/background.wav"

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
extern pthread_t 		g_resize;
extern pthread_t 		g_music;
extern pthread_attr_t 	g_atr;
extern char				g_flag;
#endif
