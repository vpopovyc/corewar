/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algoritm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:42:51 by dkosolap          #+#    #+#             */
/*   Updated: 2017/05/26 15:42:11 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "corewar.h"

void    ft_check_cycle_to_die(t_corewar *src, int n_live)
{
    t_carriage  *p;

    p = src->carriage;
    while (p)
    {
        (p->live_in_cycle > n_live) ? (n_live = p->live_in_cycle) : 0;
        p->live_in_cycle = 0; // сбросить во всех каретках счетчик циклов
        p = p->next;
    }
    if (n_live >= NBR_LIVE || src->n_check == MAX_CHECKS)
    {
        src->n_check = 0;
        src->cycle_to_die = (src->cycle_to_die < CYCLE_DELTA) ? 0 : (src->cycle_to_die - CYCLE_DELTA);
    }
    else
        src->n_check++;
    src->last_cycle_to_die = 0;
}

int     ft_check_op_arg(int comand, char op) // проверка на соответсвие оп кода агументов команде
{
    int res;

    res = 0;
    if ((comand == 2 && (op != -48 || op != -112)))
        res = 1;
    else if ((comand == 3 && (op != 112 || op != 80)))
        res = 1;
    else if ((comand == 4 || comand == 5) && op != 84)
        res = 1;
    else if ((comand == 6 || comand == 7 || comand == 8) && (op != 84 && op != 100 && op != 116 && op != -108 && op != -92 && op != -76 && op != -44 && op != -12 && op != -28))
        res = 1;
    else if (comand == 10 && (op != 100 && op != 84 && op != -92 && op != -108 && op != -28 && op
                         != -44))
        res = 1;
    else if (comand == 11 && (op != 88 && op != 84 && op != 104 && op != 100 && op != 120 &&
                              op != 116))
        res = 1;
    else if (comand == 13 && (op != -112 || op != -48))
        res = 1;
    else if (comand == 14 && (op != 100 && op != 84 && op != -92 && op != -108 && op != -28 && op
                              != -44))
        res = 1;
    else if (comand == 16 && op == 64)
        res = 1;
    return (res);
}

void    ft_check_mem_cell(t_carriage *head, char *field)
{
    t_carriage *tmp;
    
    tmp = head;
    while (tmp)
    {
        if ((unsigned char)field[tmp->position] > 0 && (unsigned char)field[tmp->position] <= 16)
        {
            tmp->f = &ft_st;
        }
        else
            tmp->position = ((tmp->position - 1) != MEM_SIZE) ? (tmp->position + 1) : 0;
        tmp = tmp->next;
    }
    // проверить ячейку на соответсвие команде , если для команды есть кодирующий байт проверить его
    // присвоить в point->f адрес функции для выполнения команды
    // если ето не команда увеличить индекс каретки на поле на один
}

void    ft_increment_cycle(t_corewar *src, t_carriage *head)
{
    t_carriage *point;

    point = head;
    while (point)
    {
        // if  (point->f)
        // {
        //     point->comand_cycle--; // если указатель на функцию не налл
        // }
        if (point->comand_cycle == 0)// что указатель на функцию не налл
        {
            // g_funcs[0](src, point); // если point->comand_cycle == 0 выполнить команду
            point->comand_cycle = 0;
            printf("count %d\n", src->players_live[0]);
        }
        point = point->next;
    }
}

void ft_algoritm(t_corewar *src)
{
    src->cycle_to_die = CYCLE_TO_DIE;
    src->players_live[0] = 0;
    while (src->carriage && src->cycle_to_die != 0 && src->fdump != src->curent_cycle)
    {
        ft_check_mem_cell(src->carriage, src->field); // проверяем ячейку памяти на наличие команды если команды нет передвигаем коретку
        if (src->last_cycle_to_die == src->cycle_to_die) // проверяем можноли уменьшить cycle_To_die
        {
            src->carriage = ft_check_del_carriege(src->carriage); //проверить и удалить все каретки которые не сказали live
            ft_check_cycle_to_die(src, 0); // сброс cycle_to_die
        }
        else
            src->last_cycle_to_die++; // инкрементируем счетчик циклов к смерти
        ft_increment_cycle(src, src->carriage); // декрементируем все циклы команд в каретках и выполняет команду
        src->curent_cycle++; // инкрементируем текущий цикл
    }
    if (src->fdump != -1 && src->fdump == src->curent_cycle)
        dk_dump(src->field);
}