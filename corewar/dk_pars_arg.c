/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dk_pars_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 13:07:51 by dkosolap          #+#    #+#             */
/*   Updated: 2017/05/18 13:07:53 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_isadigitall(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (0);
	return (1);
}

void		dk_parsplayer(int fd, t_corewar *cor, int nbr, char *name)
{
	int			len;
	t_player	*new;

	len = ft_strlen(name);
	if (len <= 4 || ft_strcmp((name + len - 4), ".cor"))
		ft_error(3);
	if (nbr < 0 || nbr > MAX_PLAYERS)
		ft_error(6);
	cor->count_ply++;
	if (cor->count_ply > MAX_PLAYERS)
		ft_error(8);
	new = ft_valid_cor(fd, 0, 0);
	new->next = cor->players;
	cor->players = new;
	cor->players->number = nbr;
}

void		dk_pars_arg(int argc, char **argv, t_corewar *cor, int i)
{
	int			fd;

	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-dump") && argv[i + 1]
		&& ft_isadigitall(argv[i + 1]))
			cor->fdump = ft_atoi(argv[++i]);
		else if (!ft_strcmp(argv[i], "-v"))
			cor->verbose = 1;
		else if (!ft_strcmp(argv[i], "-n") && argv[i + 1]
		&& ft_isadigitall(argv[i + 1]) && ((i + 2) < argc))
		{
			if ((fd = open(argv[i += 2], O_RDONLY)) != -1)
				dk_parsplayer(fd, cor, ft_atoi(argv[i - 1]), argv[i]);
		}
		else if ((fd = open(argv[i], O_RDONLY)) != -1)
			dk_parsplayer(fd, cor, 0, argv[i]);
		else
			ft_error(1);
	}
}
