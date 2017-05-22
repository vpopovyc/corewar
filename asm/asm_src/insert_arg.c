/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:41:08 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/22 18:41:09 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/compilation.h"

int		ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == ' ' || c == '\f'
		|| c == '\v')
		return (1);
	else
		return (0);
}

void	insert_registres(char *reg)
{
	char t_reg;

	t_reg = (char)ft_atoi(reg + 1);
	write(g_fd_cor, &t_reg, 1);
}

void	insert_indirect(char *ind, t_hash *table)
{
	t_hash		*elem;
	short		encode;
	char		forprint;

	elem = NULL;
	if (*ind == LABEL_CHAR)
	{
		elem = get_item(ind + 1, table);
		encode = elem->bytes - g_carrige;
	}
	else
		encode = (short)ft_atoi(ind);
	forprint = (char)(encode >> 8);
	write(g_fd_cor, &forprint, 1);
	forprint = (char)(encode);
	write(g_fd_cor, &forprint, 1);
}

void	insert_direct(char *arg, char label_size, t_hash *table)
{
	int		distance;
	short	cast;
	char	forprint;

	distance = ft_atoi(arg + 1);
	if (*(arg + 1) == LABEL_CHAR)
		print_label(arg + 2, label_size, table);
	else
	{
		if (label_size)
		{
			cast = (short)distance;
			forprint = (char)(cast >> 8);
			write(g_fd_cor, &forprint, 1);
			forprint = (char)(cast);
			write(g_fd_cor, &forprint, 1);
		}
		else
			uint_compile((unsigned int)distance);
	}
}

void	insert_args(char hex_code, char *arg, t_hash *table, char opcode)
{
	if (hex_code == 1)
		insert_registres(arg);
	else if (hex_code == 2)
		insert_direct(arg, g_op[(int)opcode - 1].label_size, table);
	else if (hex_code == 3)
		insert_indirect(arg, table);
	else
		return ;
}
