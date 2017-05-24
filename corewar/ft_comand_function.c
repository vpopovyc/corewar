/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comand_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 20:15:40 by dkosolap          #+#    #+#             */
/*   Updated: 2017/05/23 20:43:01 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "corewar.h"

void    ft_live(t_corewar *src, t_carriage *p)
{
    int value;
    
    p->posinion++;
    value = (src->game_field[p->posinion++] << 24) | (src->game_field[p->posinion++] << 16) | (src->game_field[p->posinion++] << 8) | (src->game_field[p->posinion++]);
    if (value >= 1 && value <= src->count_ply)
        src->players_live[value - 1]++;
    ft_bzero(p->arg, 16);
}

void    ft_add(t_corewar *data, t_carriage *src)
{
    src->posinion++;
    if (data->game_field[src->posinion] == 84)
    {
        src->posinion++;
        src->arg[1] = data->game_field[src->posinion++];
        src->arg[2] = data->game_field[src->posinion++];
        src->arg[3] = data->game_field[src->posinion++];
        if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
            src->reg[src->arg[3]] = src->reg[src->arg[1]] + src->reg[src->arg[2]];
    }
    ft_bzero(src->arg, 16);
}

void    ft_sub(t_corewar *data, t_carriage *src)
{
    src->posinion++;
    if (data->game_field[src->posinion] == 84)
    {
        src->posinion++;
        src->arg[1] = data->game_field[src->posinion++];
        src->arg[2] = data->game_field[src->posinion++];
        src->arg[3] = data->game_field[src->posinion++];
        if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
            src->reg[src->arg[3]] = src->reg[src->arg[1]] - src->reg[src->arg[2]];
    }
    ft_bzero(src->arg, 16);
}