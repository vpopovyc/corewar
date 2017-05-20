/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 15:20:52 by dkosolap          #+#    #+#             */
/*   Updated: 2017/05/12 15:20:53 by dkosolap         ###   ########.fr       */
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

//void		dk_sort_ply(t_corewar *cor)
//{
//	t_player	*sort;
//	int			i;
//
//	i = 1;
//}


int			main(int argc, char **argv)
{
	int			fd;
	t_corewar	cor;
	t_player	*tmp;

	fd = 0;
	cor.curent_cycle = 0;
	cor.fdump = -1;
	cor.verbose = 0;
	cor.players = NULL;
	cor.count_ply = 0;
	if (argc > 1)
	{
		dk_pars_arg(argc, argv, &cor, 0);
		if (!cor.count_ply)
			ft_error(8);
		tmp = cor.players;
		while (tmp)
		{
//			ft_printf("%s\n", tmp->name);
			tmp = tmp->next;
		}
	}
	else
		ft_error(12);
    ft_create_field_and_carriage(&cor, 0, 0, -2);



    return (0);
}
