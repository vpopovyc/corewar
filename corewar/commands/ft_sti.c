#include "../corewar.h"

static void    ft_sti_1(t_corewar *data, t_carriage *src, char op_code, int index)
{
    if (op_code == 88 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER)
    {
        index = src->reg[src->arg[2]] + src->arg[3];
        data->game_field[ft_if_negative(index)] = src->reg[src->arg[1]] >> 24;
        data->game_field[ft_if_negative(index + 1)] = src->reg[src->arg[1]] >> 16;
        data->game_field[ft_if_negative(index + 2)] = src->reg[src->arg[1]] >> 8;
        data->game_field[ft_if_negative(index + 3)] = src->reg[src->arg[1]];
        ft_write_meta(data, src->name, index);
    }
    else if (op_code == 84 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
    {
        index = src->reg[src->arg[2]] + src->reg[src->arg[3]];
        data->game_field[ft_if_negative(index)] = src->reg[1] >> 24;
        data->game_field[ft_if_negative(index + 1)] = src->reg[1] >> 16;
        data->game_field[ft_if_negative(index + 2)] = src->reg[1] >> 8;
        data->game_field[ft_if_negative(index + 3)] = src->reg[1];
        ft_write_meta(data, src->name, index);
    }
}

static void    ft_sti_2(t_corewar *data, t_carriage *src, char op_code, int index)
{
    if (op_code == 104 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
    {
        index = src->arg[2] + src->arg[3];
        data->game_field[ft_if_negative(index)] = src->reg[src->arg[1]] >> 24;
        data->game_field[ft_if_negative(index + 1)] = src->reg[src->arg[1]] >> 16;
        data->game_field[ft_if_negative(index + 2)] = src->reg[src->arg[1]] >> 8;
        data->game_field[ft_if_negative(index + 3)] = src->reg[src->arg[1]];
        ft_write_meta(data, src->name, index);
    }
    else if (op_code == 100 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
    {
        index = src->arg[2] + src->reg[src->arg[3]];
        data->game_field[ft_if_negative(index)] = src->reg[src->arg[1]] >> 24;
        data->game_field[ft_if_negative(index + 1)] = src->reg[src->arg[1]] >> 16;
        data->game_field[ft_if_negative(index + 2)] = src->reg[src->arg[1]] >> 8;
        data->game_field[ft_if_negative(index + 3)] = src->reg[src->arg[1]];
        ft_write_meta(data, src->name, index);
    }
}

static void    ft_sti_3(t_corewar *data, t_carriage *src, char op_code, int index)
{
    if (op_code == 120 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
    {
        index = data->game_field[ft_if_negative(src->arg[2])] + src->arg[3];
        data->game_field[ft_if_negative(index)] = src->reg[src->arg[1]] >> 24;
        data->game_field[ft_if_negative(index + 1)] = src->reg[src->arg[1]] >> 16;
        data->game_field[ft_if_negative(index + 2)] = src->reg[src->arg[1]] >> 8;
        data->game_field[ft_if_negative(index + 3)] = src->reg[src->arg[1]];
        ft_write_meta(data, src->name, index);
    }
    else if (op_code == 116 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
    {
        index = data->game_field[ft_if_negative(src->arg[2])] + src->reg[src->arg[3]];
        data->game_field[ft_if_negative(index)] = src->reg[src->arg[1]] >> 24;
        data->game_field[ft_if_negative(index + 1)] = src->reg[src->arg[1]] >> 16;
        data->game_field[ft_if_negative(index + 2)] = src->reg[src->arg[1]] >> 8;
        data->game_field[ft_if_negative(index + 3)] = src->reg[src->arg[1]];
        ft_write_meta(data, src->name, index);
    }
}

void ft_sti(t_corewar *data, t_carriage *src)
{
    char    op_code;
    int     index;
    
    op_code = data->game_field[src->position + 1];
    index = 0;
    if (op_code == 88 || op_code == 84 || op_code == 104 || op_code == 100 || op_code == 120 || op_code == 116)
        ft_take_arg(data, src, 0, data->game_field[src->position + 1]);
    if (op_code == 88 || op_code == 84)
        ft_sti_1(data, src, op_code, index);
    else if (op_code == 104 || op_code == 100)
        ft_sti_2(data, src, op_code, index);
    else if (op_code == 120 || op_code == 116)
        ft_sti_3(data, src, op_code, index);
    else
        ft_inc_index(src);
    ft_bzero(src->arg, 16);
}
