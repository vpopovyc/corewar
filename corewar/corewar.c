/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 15:20:52 by dkosolap          #+#    #+#             */
/*   Updated: 2017/05/30 19:00:26 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_error(int n)
{
	ft_printf("\x1b[41m");
	(n == 1) ? ft_printf("Invalid arguments !") : 0;
	(n == 2) ? ft_putstr("File doesn`t open, maybe wrong file name !") : 0;
	(n == 3) ? ft_putstr("Doesn`t right file format !") : 0;
	(n == 4) ? ft_putstr("Invalid [-dump N] cycle !") : 0;
	(n == 5) ? ft_putstr("Invalid player's binary code !") : 0;
	(n == 6) ? ft_printf("Invalid [-n N[0-%i]] flag!", MAX_PLAYERS) : 0;
	(n == 7) ? ft_putstr("Invalid player's binary code !") : 0;
	(n == 8) ? ft_putstr("Wrong number of players !") : 0;
	(n == 10) ? ft_putstr("Can`t read from file !") : 0;
	(n == 11) ? ft_putstr("Invalid magic !") : 0;
	(n == 12) ? ft_printf("Wrong number of arguments !") : 0;
	ft_printf("\x1b[0m\n\x1b[36m");
	ft_printf("Usage: ./corewar [-dump N[0-");
	ft_printf("%i] | -v] [[-n N] champion1.cor] ...\n", MAX_PLAYERS);
	ft_printf("\t-v\t: Ncurses output mode\n");
	ft_printf("\t-dump N\t: Dumps memory after N cycles then exits\n");
	ft_printf("\t-n N\t: sets the number of the next player\n");
	ft_printf("\x1b[0m");
	exit(-1);
}

void		dk_dump(char *addr)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{	
		if ((unsigned char)addr[i])
			ft_printf("\x1b[32m");
		ft_printf("%.2x ", (unsigned char)addr[i]);
		ft_printf("\x1b[0m");
		if ((i + 1) % 64 == 0)
			ft_printf("\n");
	}
}

int			main(int argc, char **argv)
{
	int			fd;
	t_corewar	*cor;

	fd = 0;
	cor = (t_corewar *)malloc(sizeof(t_corewar));
	cor = ft_memset(cor, 0, sizeof(t_corewar));   
	cor->fdump = -1;
	if (argc > 1)
	{
		dk_pars_arg(argc, argv, cor, 0);
		if (!cor->count_ply)
			ft_error(8);
		dk_sort_ply(&cor->players, cor->count_ply);
	}
	else
		ft_error(12);
	ft_create_field_and_carriage(cor, 0, -2);
	cor->players_live = (int *)malloc(sizeof(int) * cor->count_ply);
	g_funcs[0] = &ft_live;
	g_funcs[1] = &ft_ld;
	g_funcs[2] = &ft_st;
	g_funcs[3] = &ft_add;
	g_funcs[4] = &ft_sub;
	g_funcs[5] = &ft_and_or_xor;
	g_funcs[6] = &ft_and_or_xor;
	g_funcs[7] = &ft_and_or_xor;
	g_funcs[8] = &ft_zjmp;
	g_funcs[9] = &ft_ldi_lldi;
	g_funcs[10] = &ft_sti;
	g_funcs[11] = &ft_fork;
	g_funcs[12] = &ft_lld;
	g_funcs[13] = &ft_ldi_lldi;
	g_funcs[14] = &ft_lfork;
	g_funcs[15] = &ft_aff;
	ft_algoritm(cor);
	// printf("meta\n");
    // dk_dump(cor->meta_data);
    return (0);
}
