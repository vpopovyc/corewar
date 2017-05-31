
#include "../corewar.h"

void	ft_lfork(t_corewar *data, t_carriage *src)
{
    t_carriage *point;
    
    ft_inc_index(src);
	src->arg[1] = (short)((unsigned char)data->game_field[ft_inc_index(src)] << 8) | (unsigned char)data->game_field[ft_inc_index(src)];
    point = data->carriage;
    while (point->next)
        point = point->next;
    src->arg[1] = ft_if_negative(src->position + src->arg[1]);
    point->next = ft_create_carriage(src->arg[1], src->reg[1], src);
    ft_bzero(src->arg, 16);
}
