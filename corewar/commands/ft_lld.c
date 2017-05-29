
#include "corewar.h"

void    ft_lld(t_corewar *data, t_carriage *src)
{
    if (data->game_field[src->position + 1] == -48)
    {
        ft_take_arg(data, src, 0, data->game_field[src->position]);
        if (src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER)
        {
            src->reg[src->arg[2]] = (data->game_field[ft_if_negative(src->position - 5 + src->arg[1])] << 24) | (data->game_field[ft_if_negative(src->position - 5 + src->arg[1] + 1)] << 16) | (data->game_field[ft_if_negative(src->position - 5 + src->arg[1] + 2)] << 8) | data->game_field[ft_if_negative(src->position - 5 + src->arg[1] + 3)];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
    }
    else if (data->game_field[src->position + 1] == -112)
    {
        ft_take_arg(data, src, 0, data->game_field[src->position]);
        if (src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER)
        {
            src->reg[src->arg[2]] = src->arg[1];
            src->carry = (src->carry == 1) ? 0 : 1;
        }
    }
    else
        ft_inc_index(src);
    ft_bzero(src->arg, 16);
}
