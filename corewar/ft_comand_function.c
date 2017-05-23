#include "corewar.h"

void    ft_live(t_corewar *src, t_carriage *p)
{
    int value;
    
    p->posinion++;
    value = (src->game_field[p->posinion++] << 24) + (src->game_field[p->posinion++] << 16) + (src->game_field[p->posinion++] << 8) + (src->game_field[p->posinion++]);
    if (-value >= 1 && -value <= src->count_ply)
        src->players_live[-value - 1]++;
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











void    ft_ld(t_corewar *data, t_carriage *src)
{
    src->posinion++;
    if (data->game_field[src->posinion] == -48)
    {
        src->posinion++;
        src->arg[1] = (data->game_field[src->posinion++] << 8) | data->game_field[src->posinion++];
        src->arg[2] = data->game_field[src->posinion++];
        if (src->arg[2] >= 1 && src->arg[2] <= REG_NUMBER)
        {
            if (src->arg[1] <= IDX_MOD)
                src->reg[src->arg[2]] = data->game_field[src->posinion - 5 + src->arg[1]];
            else
                src->reg[src->arg[2]] = data->game_field[src->posinion - 5 + (src->arg[1] % IDX_MOD)];
        }
    }
    else if (data->game_field[src->posinion] == -112)
    {
        src->posinion++;
        src->arg[1] = (data->game_field[src->posinion++] << 8) | data->game_field[src->posinion++];
        src->arg[2] = data->game_field[src->posinion++];
        if (src->arg[2] >= 1 && src->arg[2] <= REG_NUMBER)
            src->reg[src->arg[2]] = src->arg[1];
    }
    ft_bzero(src->arg, 16);
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







void    ft_aff(t_carriage *src)
{
    if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
        ft_putnbr(src->reg[src->arg[1]]);
}

// нужны 16 функций отвечающих за выполнения команд !!!!!!!!!!!!
// при выполнении команды передвигать каретку на байт следующий за командой и аргументами байт
// в функции live инкрементировать счетчик соответсвующего игрока
