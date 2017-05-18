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
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

// t_player	*ft_valid_cor(int fd)
// {
// 	t_player	*new;

// 	new = (t_player *)malloc(sizeof(t_player));
// 	new->name = "zork";
// 	new->comment = "I'm a live";
// 	new->comand_code = "0b6801000f00010664010000000001010000000109fffb";
// 	new->number = 0;
// 	new->size = fd;
// 	new->next = NULL;
// 	return (new);
// }

void		addplayer(t_player **pl, t_player *new)
{
	if ((pl) && (new))
	{
		new->next = *pl;
		*pl = new;
	}
}

void		dk_parsplayer(int fd, t_corewar *cor, int *nbr)
{
	// if (*nbr < 1 || *nbr > MAX_PLAYERS)
	// {
		// ft_error(6);
	// }
	addplayer(&cor->players, ft_valid_cor(fd, 0, 0));
	cor->players->number = *nbr;
	if (*nbr)
		*nbr = 0;
}

void		dk_pars_arg(int argc, char **argv, t_corewar *cor, int i)
{
	int			fd;
	int			nbr;
	int			len;

	nbr = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-dump") && argv[i + 1]
		&& ft_isadigitall(argv[i + 1]))
			cor->fdump = ft_atoi(argv[++i]);
		else if (!ft_strcmp(argv[i], "-v"))
			cor->verbose = 1;
		else if (!ft_strcmp(argv[i], "-n") && argv[i + 1]
		&& ft_isadigitall(argv[i + 1]))
			nbr = ft_atoi(argv[++i]);
		else if ((fd = open(argv[i], O_RDONLY)) != -1)
		{
			len = ft_strlen(argv[i]);
			if (len <= 4 || ft_strcmp((argv[i] + len - 4), ".cor"))
				ft_error(3);
			dk_parsplayer(fd, cor, &nbr);
		}
		else
			ft_error(2);
	}
}
