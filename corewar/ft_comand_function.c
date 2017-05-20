#include "corewar.h"

void    ft_live(t_corewar *src, int value)
{
    if ((value * -1) >= 1 && (value * -1) <= src->count_ply)
        src->players_live[(value * (-1)) - 1]++;
}

void    ft_ld(t_corewar *src, t_carriage *p)
{
    if (p->arg[0] == -48 && p->arg[2] >= 0 && p->arg[2] <= REG_NUMBER) // indirect
    {
        if (p->posinion + p->arg[1] >= MEM_SIZE)
            p->reg[p->arg[2]] = src->game_field[p->posinion + p->arg[1] - MEM_SIZE]; // если нужний адрес в начале, при переполнении адереса
        else
            p->reg[p->arg[2]] = src->game_field[p->arg[1]];
        p->carry = (p->carry == 1) ? 0 : 1;
    }
    else if (p->arg[0] == -112 && p->arg[2] >= 0 && p->arg[2] <= REG_NUMBER) //direct
    {
        p->reg[p->arg[2]] = p->arg[1];
        p->carry = (p->carry == 1) ? 0 : 1;
    }
}

void    ft_st(t_corewar *src, t_carriage *p)
{
    if (p->arg[0] == 112 && p->arg[2] >= 0 && p->arg[2] <= REG_NUMBER) //ind
    {
//        дописать тут !!!!!!!!!!!!!!!!!
    }
    else if (p->arg[0] == 80 && p->arg[2] >= 0 && p->arg[2] <= REG_NUMBER) //dir
    {
        p->arg[1] = p->posinion + (p->arg[1] % IDX_MOD);
        if (p->posinion + p->arg[1] >= MEM_SIZE)
            src->game_field[p->posinion + p->arg[1] -MEM_SIZE] = p->reg[p->arg[2]];
        else
            src->game_field[p->arg[1]] = p->reg[p->arg[2]];
    }
}
// (PC + (42 % IDX_MOD))
//T_REG, T_IND | T_REG



void    ft_add(t_carriage *src)
{
    if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        src->reg[src->arg[3]] = src->reg[src->arg[1]] + src->reg[src->arg[2]];
}

void    ft_sub(t_carriage *src)
{
    if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        src->reg[src->arg[3]] = src->reg[src->arg[1]] - src->reg[src->arg[2]];
}

void    ft_aff(t_carriage *src)
{
    if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
        ft_putnbr(src->reg[src->arg[1]]);
}

