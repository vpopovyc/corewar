

#include "corewar.h"

void	ft_aff(t_corewar *data, t_carriage *src)
{
    ft_inc_index(src);
    src->arg[1] = data->game_field[ft_inc_index(src)];
    if (src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
        ft_putnbr(src->reg[src->arg[1]]);
    ft_bzero(src->arg, 16);
}
