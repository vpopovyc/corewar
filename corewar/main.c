/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:31:02 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/29 16:56:19 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses/visualisation.h"

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
	ft_memset((void*)src->game_field, 0x01, MEM_SIZE / 2);
	ft_memset((void*)src->game_field + (MEM_SIZE / 2), 0x10, MEM_SIZE / 2);
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
/* tmp
 */
	init = init_ncurses();

	while (1)
	{
		pthread_mutex_lock(&g_mutex_flag);
		if (g_flag & EXIT)
			break ;
		pthread_mutex_unlock(&g_mutex_flag);
		fill_screen(init, src);
		algo_event_managment();
		usleep (5 * 100000);
	}
	end_ncurses(init);
	return (0);
}