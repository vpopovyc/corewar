#include "corewar.h"

t_carriage *ft_check_del_carriege(t_carriage *src)
{
    t_carriage *point;
    
    point = src;
    while (point)
    {
        if (point->live_in_cycle == 0)
        {
            src = ft_del_carriage(src, point);
            point = src;
        }
        else
            point = point->next;
    }
    return (src);
}

t_carriage *ft_del_carriage(t_carriage *src, t_carriage *del)
{
    t_carriage *head;
    t_carriage *previous;
    
    if (del == src)
        head = src->next;
    else
    {
        head = src;
        previous = src;
        while (src != del)
        {
            previous = src;
            src = src->next;
        }
        previous->next = src->next;
    }
    free(src);
    return (head);
}

t_carriage *ft_create_carriage(unsigned int posinion, int num)
{
    t_carriage *new;
 
    new = (t_carriage*)malloc(sizeof(t_carriage));
    new->comand_cycle = 0;
    new->f = NULL;
    new->live_in_cycle = 0;
    new->position = posinion;
    new->next = NULL;
    ft_bzero(new->reg, (REG_NUMBER * 4));
    new->reg[1] = num;
    return (new);
}

void    ft_count_free_mem_size(t_player *head, int *free_space)
{
    t_player    *point;
    int         sum_size;
    int         n_player;

    sum_size = 0;
    n_player = 0;
    point = head;
    while (point)
    {
        sum_size += point->size;
        n_player++;
        point = point->next;
    }
    *free_space = (MEM_SIZE - sum_size) / n_player;
}

void    ft_create_field_and_carriage(t_corewar *src, int free_space, int n, int num)
{
    t_player        *point;
    char            *p;
    t_carriage      *carriage;
    
    src->game_field = ft_strnew(MEM_SIZE - 1);
    src->carriage = ft_create_carriage(0, -1);
    src->carriage->reg[1] = -1;
    ft_count_free_mem_size(src->players, &free_space);
    carriage = src->carriage;
    point = src->players;
    p = src->game_field;
    while (point)
    {
        if (n == 0)
            ft_memcpy(p, point->code, point->size);
        else
        {
            carriage->next = ft_create_carriage(n, num--);
            carriage = carriage->next;
            ft_memcpy(p + n, point->code, point->size);
        }
        n += point->size + free_space;
        point = point->next;
    }
}
