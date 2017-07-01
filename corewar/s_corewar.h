/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_corewar.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:22:36 by dkosolap          #+#    #+#             */
/*   Updated: 2017/06/06 19:26:25 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __S_COREWAR_H
# define __S_COREWAR_H
# include "corewar.h"

typedef struct			s_corewar
{
	struct s_player		*players;
	struct s_carriage	*carriage;
	char				*field;
	char				*meta_data;
	char				*meta_bold;
	int					*players_live;
	unsigned int		curent_cycle;
	unsigned int		cycle_to_die;
	unsigned int		last_cycle_to_die;
	unsigned int		n_check;
	int					fdump;
	int					verbose;
	int					count_ply;
	int					sec_cycle;
	char				*winer;
	char				n_winer;
	unsigned int		n_processes;
}						t_corewar;

#endif
