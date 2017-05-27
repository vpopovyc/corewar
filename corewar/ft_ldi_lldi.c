
#include "corewar.h"

void    ft_get_data(t_corewar *data, t_carriage *src, int index, char comd)
{
    src->reg[src->arg[3]] = (data->game_field[ft_if_negative(index)] << 24) | (data->game_field[ft_if_negative(index + 1)] << 16) |  (data->game_field[ft_if_negative(index + 2)] << 8) |  data->game_field[ft_if_negative(index + 3)];
    if (comd == 14)
        src->carry = (src->carry == 1) ? 0 : 1;
}

void    ft_ldi_lldi_1(t_corewar *data, t_carriage *src, char op, char comd)
{
    int index;
    
    if (op == 100 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
    {
        index = src->reg[src->arg[1]] + src->arg[2];
        ft_get_data(data, src, index, comd);
    }
    else if (op == 84 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER)
    {
        index = src->reg[src->arg[1]] + src->reg[src->arg[2]];
        ft_get_data(data, src, index, comd);
    }
}


void         ft_ldi_lldi_2(t_corewar *data, t_carriage *src, char op, char comd)
{
    int index;
    
    if (op == -92 && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
    {
        index = src->arg[1] + src->arg[2];
        ft_get_data(data, src, index, comd);
    }
    else if (op == -108 && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
    {
        index = src->arg[1] + src->reg[src->arg[2]];
        ft_get_data(data, src, index, comd);
    }
}


void  ft_ldi_lldi_3(t_corewar *data, t_carriage *src, char op, char comd)
{
    int index;
    
    if (op == -44 && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
    {
        index = (short)((unsigned char)data->game_field[ft_if_negative(src->arg[1])] << 8) | (unsigned char)data->game_field[ft_if_negative(src->arg[1] + 1)];
        index += src->reg[src->arg[2]];
        ft_get_data(data, src, index, comd);
    }
    else if (op == -28 && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
    {
        index = (short)((unsigned char)data->game_field[ft_if_negative(src->arg[1])] << 8) | (unsigned char)data->game_field[ft_if_negative(src->arg[1] + 1)];
        index += src->arg[2];
        ft_get_data(data, src, index, comd);
    }
}

void ft_ldi_lldi(t_corewar *data, t_carriage *src)
{
    char    comd;
    char    op;
    
    comd = data->game_field[src->position];
    op = data->game_field[ft_if_negative(src->position + 1)];
    if (op == 100 || op == 84 || op == -92 || op == -108 || op == -44 || op == -28)
        ft_take_arg(data, src, 0, comd);
    if (op == 100 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        ft_ldi_lldi_1(data, src, op, comd);
    else if (op == 84 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER)
        ft_ldi_lldi_1(data, src, op, comd);
    else if (op == -92 && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        ft_ldi_lldi_2(data, src, op, comd);
    else if (op == -108 && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        ft_ldi_lldi_2(data, src, op, comd);
    else if (op == -44 && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        ft_ldi_lldi_3(data, src, op, comd);
    else if (op == -28 && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
        ft_ldi_lldi_3(data, src, op, comd);
    else
        ft_inc_index(src);
    ft_bzero(src->arg, 16);
}