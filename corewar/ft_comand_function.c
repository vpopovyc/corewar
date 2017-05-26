#include "corewar.h"

void    ft_live(t_corewar *data, t_carriage *src)
{
    ft_inc_index(src);
    src->arg[1] = (data->game_field[ft_inc_index(src)] << 24) | (data->game_field[ft_inc_index(src)] << 16) | (data->game_field[ft_inc_index(src)] << 8) | (data->game_field[ft_inc_index(src)]);
    if (-src->arg[1] >= 1 && -src->arg[1] <= data->count_ply)
        data->players_live[-src->arg[1] - 1]++;
    ft_bzero(src->arg, 16);
}

void    ft_zjmp(t_corewar *data, t_carriage *src)
{
    ft_inc_index(src);
    if (src->carry == 1)
    {
        src->arg[1] = (data->game_field[ft_inc_index(src)] << 8) | data->game_field[ft_inc_index(src)];
        src->position = ft_if_negative(src->position - 3 + src->arg[1]);
        ft_bzero(src->arg, 16);
    }
    else
        src->position = ft_if_negative(src->position + 2);
}

void    ft_add(t_corewar *data, t_carriage *src)
{
    if (data->game_field[src->position + 1] == 84)
    {
        ft_take_arg(data, src, 0, data->game_field[src->position]);
        if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        {
            src->reg[src->arg[3]] = src->reg[src->arg[1]] + src->reg[src->arg[2]];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
     }
    else
        ft_inc_index(src);
    ft_bzero(src->arg, 16);
}

void    ft_sub(t_corewar *data, t_carriage *src)
{
    if (data->game_field[src->position + 1] == 84)
    {
        ft_take_arg(data, src, 0, data->game_field[src->position]);
        if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        {
            src->reg[src->arg[3]] = src->reg[src->arg[1]] - src->reg[src->arg[2]];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
    }
    else
        ft_inc_index(src);
    ft_bzero(src->arg, 16);
}

void    ft_ld(t_corewar *data, t_carriage *src)
{
    if (data->game_field[src->position + 1] == -48)
    {
        ft_take_arg(data, src, 0, data->game_field[src->position]);
        if (src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER)
            src->reg[src->arg[2]] = (data->game_field[ft_if_negative(src->position - 5 + src->arg[1])] << 24) | (data->game_field[ft_if_negative(src->position - 5 + src->arg[1] + 1)] << 16) | (data->game_field[ft_if_negative(src->position - 5 + src->arg[1] + 2)] << 8) | data->game_field[ft_if_negative(src->position - 5 + src->arg[1] + 3)];
    }
    else if (data->game_field[src->position + 1] == -112)
    {
        ft_take_arg(data, src, 0, data->game_field[src->position]);
        if (src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER)
            src->reg[src->arg[2]] = src->arg[1];
    }
    else
        ft_inc_index(src);
    ft_bzero(src->arg, 16);
}

void    ft_st(t_corewar *data, t_carriage *src)
{
    if (data->game_field[src->position + 1] == 112)
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
        {
            src->arg[2] = src->position - 5 + (src->arg[2] % IDX_MOD);
            
//            data->game_field[src->arg[2]] = (src->arg[1] >> 24) & 0xFF;
//            data->game_field[ft_if_negative(src->arg[2] + 1)]  = (src->arg[1] >> 16) & 0xFF;
//            data->game_field[ft_if_negative(src->arg[2] + 2)] = (src->arg[1] >> 8) & 0xFF;
//            data->game_field[ft_if_negative(src->arg[2] + 3)] = src->arg[1] & 0xFF;
        
            ft_memcpy((data->game_field + ft_if_negative(src->arg[2])), &src->reg[src->arg[1]], 4); // не правильно записываеться на карту

        }
    }
    else if (data->game_field[src->position + 1] == 80)
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER)
            src->reg[src->arg[2]] = src->reg[src->arg[1]];
    }
    else
        ft_inc_index(src);
    ft_bzero(src->arg, 16);
}


void    ft_fork(t_corewar *data, t_carriage *src)
{
    t_carriage *point;
    
    ft_inc_index(src);
    src->arg[1] = (data->game_field[ft_inc_index(src)] << 16) | data->game_field[ft_inc_index(src)];
    point = data->carriage;
    while (point->next)
        point = point->next;
    src->arg[1] = ft_if_negative(src->position + (src->arg[1] % IDX_MOD));
    point->next = ft_create_carriage(src->arg[1], src->reg[1]);
    ft_bzero(src->arg, 16);
}

void    ft_lfork(t_corewar *data, t_carriage *src)
{
    t_carriage *point;
    
    ft_inc_index(src);
    src->arg[1] = (data->game_field[ft_inc_index(src)] << 16) | data->game_field[ft_inc_index(src)];
    point = data->carriage;
    while (point->next)
        point = point->next;
    src->arg[1] = ft_if_negative(src->position + src->arg[1]);
    point->next = ft_create_carriage(src->arg[1], src->reg[1]);
    ft_bzero(src->arg, 16);
}

void    ft_aff(t_corewar *data, t_carriage *src)
{
    ft_inc_index(src);
    src->arg[1] = data->game_field[ft_inc_index(src)];
    if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
        ft_putnbr(src->reg[src->arg[1]]);
    ft_bzero(src->arg, 16);
}

void    ft_take_arg(t_corewar *data, t_carriage *src, int i, int comand) // i == 0  / вызываеться при командах с опкодом
{
    comand = data->game_field[src->position];
    ft_inc_index(src);
    src->arg[0] = data->game_field[src->position];
    src->arg[1] = (unsigned char)data->game_field[src->position] >> 6;
    src->arg[2] = (unsigned char)data->game_field[src->position] << 2;
    src->arg[2] = (unsigned char)src->arg[2] >> 6;
    src->arg[3] = (unsigned char)data->game_field[src->position] << 4;
    src->arg[3] = (unsigned char)src->arg[3] >> 6;
    ft_inc_index(src);
    while (++i < 4)
    {
        if (src->arg[i] == 1)
            src->arg[i] = data->game_field[ft_inc_index(src)];
        else if (src->arg[i] == 2)
        {
            if (comand == 2 || comand == 6 || comand == 7 || comand == 9 || comand == 13)
                src->arg[i] = (data->game_field[ft_inc_index(src)] << 24) | (data->game_field[ft_inc_index(src)] << 16) | (data->game_field[ft_inc_index(src)] << 8) | data->game_field[ft_inc_index(src)];
            else // dir == 2 байта
                src->arg[i] = (data->game_field[ft_inc_index(src)] << 8) | data->game_field[ft_inc_index(src)];
        }
        else if (src->arg[i] == 3)
            src->arg[i] = (data->game_field[ft_inc_index(src)] << 8) | data->game_field[ft_inc_index(src)];
    }
}

int     ft_inc_index(t_carriage *src) // если индекс выходить за поле, индекс сбиваеться на ноль
{
    int res;
    
    res = src->position;
    if ((src->position + 1) == MEM_SIZE)
        src->position = 0;
    else
        src->position++;
    return (res);
}

int     ft_if_negative(int index)
{
    int res;
    
    if (index < 0)
        res = MEM_SIZE + index - 1;
    if (index >= MEM_SIZE)
        res = index % MEM_SIZE;
    else
        res = index;
    return (res);
}



























void    ft_and(t_corewar *data, t_carriage *src)
{
    if (data->game_field[src->position + 1] == 84) // reg reg reg
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] && src->arg[3] <= REG_NUMBER)
        {
            src->reg[src->arg[3]] = src->reg[src->arg[1]] & src->reg[src->arg[2]];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
    }
    else if (data->game_field[src->position + 1] == -108) // dir reg reg
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        {
            src->reg[src->arg[3]] = src->arg[1] & src->reg[src->arg[2]];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
    }
    else if (data->game_field[src->position + 1] == -44) //ind reg reg
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        {
            src->arg[1] = src->position - 5 + src->arg[1];
            while (src->arg[1] > MEM_SIZE)
                src->arg[1] -= MEM_SIZE;
            src->reg[src->arg[3]] = ((data->game_field[src->arg[1]] << 8) | data->game_field[src->arg[1] + 1]) & src->reg[src->arg[2]];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
    }
    else if (data->game_field[src->position + 1] == 116) // reg ind reg
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        {
            src->arg[1] = src->position - 5 + src->arg[2];
            while (src->arg[2] > MEM_SIZE)
                src->arg[2] -= MEM_SIZE;
            src->reg[src->reg[3]] = data->game_field[src->arg[2]] & src->reg[src->arg[1]];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
    }
    else if (data->game_field[src->position + 1] == 100) // reg dir reg
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        {
            src->reg[src->arg[3]] = src->arg[1] & src->arg[2];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
    }
    else if (data->game_field[src->position + 1] == -76) // dir ind reg
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        {
            src->arg[2] = src->position - 8 + src->arg[2];
            while (src->arg[2] > MEM_SIZE)
                src->arg[2] -= MEM_SIZE;
            src->reg[src->arg[3]] = src->arg[1] & data->game_field[src->arg[2]];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
    }
    else if (data->game_field[src->position + 1] == -92) // dir dir reg
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        {
            src->reg[src->arg[3]] = src->arg[1] & src->arg[2];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
        
    }
    else if (data->game_field[src->position + 1] == -12)// ind ind reg
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        {
            src->arg[1] = src->position - 6 + src->arg[1];
            while (src->arg[1] > MEM_SIZE)
                src->arg[1] -= MEM_SIZE;
            src->arg[2] = src->position - 6 + src->arg[2];
            while (src->arg[2] > MEM_SIZE)
                src->arg[2] -= MEM_SIZE;
            src->reg[src->arg[3]] = data->game_field[src->arg[1]] & data->game_field[src->arg[2]];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
    }
    else if (data->game_field[src->position + 1] == -28) // ind dir reg
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        {
            src->arg[1] = src->position - 8 + src->arg[1];
            while (src->arg[1] > MEM_SIZE)
                src->arg[1] -= MEM_SIZE;
            src->reg[src->arg[3]] = src->arg[2] & data->game_field[src->arg[1]];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
    }
    else
        ft_inc_index(src);
    ft_bzero(src->arg, 16);
}






