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

void	ft_error(int n, char *str)
{
	ft_printf("\x1b[41m");
	(n == 1) ? ft_printf("Wrong number of arguments !") : 0;
	(n == 2) ? ft_putstr("File doesn`t open, maybe wrong file name !") : 0;
	(n == 3) ? ft_putstr("Invalid [-dump N] cycle !") : 0;
	(n == 4) ? ft_putstr("Invalid [[-n N] champion1.cor] name !") : 0;
	(n == 5) ? ft_putstr("Invalid player's binary code !") : 0;
	(n == 6) ? ft_putstr("To match players !") : 0;
	ft_printf("\x1b[0m\n\x1b[36m");
	ft_printf("Usage: %s [-dump N | -v] [[-n N] champion1.cor] ...\n", str);
	ft_printf("\t-v\t: Ncurses output mode\n");
	ft_printf("\t-dump N\t: Dumps memory after N cycles then exits\n");
	ft_printf("\t-n N\t: sets the number of the next player\n");
	ft_printf("\x1b[0m");
	exit(-1);
}

int		ft_isadigitall(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void	dk_parsplayer(int fd, t_corewar *cor)
{
	ft_printf("here\n");
}

void	dk_pars_arg(int argc, char **argv, t_corewar *cor)
{
	int		i;
	int		fd;

	i = 0;
	fd = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-dump"))
		{
			if (argv[++i] && ft_isadigitall(argv[i]))
				cor->fdump = ft_atoi(argv[i]);
		}
		else if (!ft_strcmp(argv[i], "-v"))
			cor->verbose = 1;
		else if ((fd = open(argv[i], O_RDONLY) != -1))
			dk_parsplayer(fd, cor);
		else
			ft_error(2, argv[0]);
	}
}

int		main(int argc, char **argv)
{
	int			fd;
	t_corewar	cor;

	fd = 0;
	cor.cycle = 0;
	cor.cycle_to_die = 1536;
	cor.cycle_delta = 1536;
	cor.fdump = -1;
	cor.verbose = 0;
	cor.players = NULL;
	if (argc > 1)
	{
		dk_pars_arg(argc, argv, &cor);
		ft_printf("%i %i\n", cor.fdump, cor.verbose);
	}
	else
		ft_error(1, argv[0]);
	return 0;
}
