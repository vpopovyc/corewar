/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:42:16 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/02 16:14:32 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_open(char *name, t_file *src)
{
	src->fd = open(name);
	(src->fd < 0) ? ft_error(3) : 0; 
}

void	ft_error(int n)
{
	ft_putstr("\033[0;31m");
	ft_putstr("ERROR\n");
	(n == 1) ? ft_putstr("Memory allocation error !\n") : 0;
	(n == 2) ? ft_putstr("Wrong number of arguments!\n") : 0;
    (n == 3) ? ft_putstr("File doesn`t open, maybe wrong file name\n") : 0;
    (n == 4) ? ft_putstr("It`s not possible to read the file\n") : 0;
    (n == 5) ? ft_putstr("It`s not possible to close the file\n") : 0;
	ft_putstr("USAGE: ./lem-in <mapfile name>\n");
	exit(-1);
}

int		main(int argc, char **argv)
{
	t_file *new;

	(!(new = (t_file*)malloc(sizeof(t_file)))) ? ft_error(1) : 0;
	(argc != 2) ? ft_error(2) : ft_open(argv[1], new);

	return (0);
}
