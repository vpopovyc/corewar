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

t_carriage *ft_create_carriage(unsigned int posinion, int num, t_carriage *data)
{
    t_carriage *new;
 
    new = (t_carriage*)malloc(sizeof(t_carriage));
    new->comand_cycle = 0;
    new->f = NULL;
    new->live_in_cycle = 0;
    new->position = posinion;
    new->next = NULL;
    ft_bzero(new->reg, (REG_NUMBER * 4));
    if (data)
    {
        ft_memcpy(new->reg, data->reg, 4 * REG_NUMBER);
        new->carry = data->carry;
        new->name = (char)new->reg[1];
    }
    else
    {
        new->reg[1] = num;
        new->name = (char)num;
        new->carry = 0;
    }
    return (new);
}

void    dk_field_meta(char *meta, int name, int len)
{
    int     i;

    i = -1;
    while (++i < len)
        meta[i] = -name;
}

void    ft_create_field_and_carriage(t_corewar *src, int n, int num)
{
    t_player        *point;
    char            *p;
    t_carriage      *carriage;
    
    src->field = ft_strnew(MEM_SIZE - 1);
    src->meta_data = ft_strnew(MEM_SIZE - 1);
    src->carriage = ft_create_carriage(0, -1, NULL);
    src->carriage->reg[1] = -1;
    carriage = src->carriage;
    point = src->players;
    p = src->field;
    while (point)
    {
        if (n == 0)
            ft_memcpy(p, point->code, point->size);
        else
        {
            carriage->next = ft_create_carriage(n, num--, NULL);
            carriage = carriage->next;
            ft_memcpy(p + n, point->code, point->size);
        }
        dk_field_meta(src->meta_data + n, point->number, point->size);
        n += MEM_SIZE / src->count_ply;
        point = point->next;
    }
}



















































