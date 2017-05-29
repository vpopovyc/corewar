
#include "corewar.h"

void	ft_st(t_corewar *data, t_carriage *src)
{
    if (data->game_field[src->position + 1] == 112)
    {
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
        if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
        {
            src->arg[2] = src->position - 5 + (src->arg[2] % IDX_MOD);
            data->game_field[ft_if_negative(src->arg[2])] = (src->reg[src->arg[1]] >> 24);
            data->game_field[ft_if_negative(src->arg[2]) + 1] = (src->reg[src->arg[1]] >> 16);
            data->game_field[ft_if_negative(src->arg[2]) + 2] = (src->reg[src->arg[1]] >> 8);
            data->game_field[ft_if_negative(src->arg[2]) + 3] = (src->reg[src->arg[1]]);
            ft_write_meta(data, src->name, src->arg[2]);
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
