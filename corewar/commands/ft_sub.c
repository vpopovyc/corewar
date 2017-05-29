#include "../corewar.h"

void	ft_sub(t_corewar *data, t_carriage *src)
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
