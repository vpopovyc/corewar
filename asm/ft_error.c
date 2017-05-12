/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:08:29 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/12 12:02:51 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' ||
		c == '\r' || c == '\f' || c == '\v')
		return (1);
	else
		return (0);
}

void	ft_error(int n)
{
	ft_putstr("\033[0;31m");
	ft_putstr("ERROR\n");
	(n == 1) ? ft_putstr("Memory allocation error !\n") : 0;
	(n == 2) ? ft_putstr("Wrong number of arguments !\n") : 0;
	(n == 3) ? ft_putstr("File doesn`t open, maybe wrong file name !\n") : 0;
	(n == 4) ? ft_putstr("It`s not possible to read the file !\n") : 0;
	(n == 5) ? ft_putstr("It`s not possible to close the file !\n") : 0;
	(n == 6) ? ft_putstr("Invalid header !\n") : 0;
	(n == 7) ? ft_putstr("Name is too long !\n") : 0;
	(n == 8) ? ft_putstr("Comment is too long !\n") : 0;
	(n == 9) ? ft_putstr("Invalid label !\n") : 0;
	(n == 10) ? ft_putstr("Invalid comand !\n") : 0;
	(n == 11) ? ft_putstr("Invalid argument !\n") : 0;
	ft_putstr("USAGE: ./asm <gamer_file_name.s>\n");
	exit(-1);
}
