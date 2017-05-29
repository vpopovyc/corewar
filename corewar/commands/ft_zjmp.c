
#include "corewar.h"

void	ft_zjmp(t_corewar *data, t_carriage *src)
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
