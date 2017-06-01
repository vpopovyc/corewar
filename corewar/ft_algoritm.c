/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algoritm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:42:51 by dkosolap          #+#    #+#             */
/*   Updated: 2017/06/01 16:36:27 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ncurses/visualisation.h"
#include <time.h>

void    ft_check_cycle_to_die(t_corewar *src, int n_live)
{
    t_carriage  *p;

    p = src->carriage;
    while (p)
    {
        ((int)p->live_in_cycle > n_live) ? (n_live = p->live_in_cycle) : 0;
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
    ft_bzero(src->players_live, 4 * src->count_ply);
    src->last_cycle_to_die = 0;
}

void    ft_check_mem_cell(t_carriage *head, char *field)
{
    t_carriage *tmp;
    
    tmp = head;
    while (tmp)
    {
        if ((unsigned char)field[tmp->position] > 0 && (unsigned char)field[tmp->position] <= 16)
        {
            if (!tmp->f)
            {
                tmp->f = g_funcs[field[tmp->position] - 1];
                tmp->comand_cycle = g_op[field[tmp->position] - 1].cycles;
            }
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
        if (point->f)
            point->comand_cycle--; // если указатель на функцию не налл
        if (point->comand_cycle == 0 && point->f)// что указатель на функцию не налл
        {
            point->f(src, point); // если point->comand_cycle == 0 выполнить команду
            point->f = NULL;
            point->comand_cycle = 0;
        }
        point = point->next;
    }
}

/*
** придумай метод или переменную с помощью которой, я смогу выводить log игрока
** например, "игрок 1 сделал sti" или "игрок 2 сказал жив"
*/

int     count_carriege(t_carriage *head)
{
    int        res;

    res = 0;
    while (head)
    {
        res++;
        head = head->next;
    }
    return (res);
}

void ft_algoritm(t_corewar *src)
{
    t_init_screen   *init;

    src->winer = -src->count_ply;
    src->cycle_to_die = CYCLE_TO_DIE;
    ft_bzero(src->players_live, 4 * src->count_ply);
    init = init_ncurses();
    while (src->carriage && src->cycle_to_die != 0 && src->fdump != (int)src->curent_cycle)
    {
        /****/
        pthread_mutex_lock(&g_mutex_flag);
        if (g_flag & EXIT)
            break ;
        pthread_mutex_unlock(&g_mutex_flag);
        /****/
        ft_check_mem_cell(src->carriage, src->field); // проверяем ячейку памяти на наличие команды если команды нет передвигаем коретку
        if ((int)src->last_cycle_to_die == (int)src->cycle_to_die) // проверяем можноли уменьшить cycle_To_die
        {
            src->carriage = ft_check_del_carriege(src->carriage); //проверить и удалить все каретки которые не сказали live
            ft_check_cycle_to_die(src, 0); // сброс cycle_to_die
        }
        else
            src->last_cycle_to_die++; // инкрементируем счетчик циклов к смерти
        ft_increment_cycle(src, src->carriage); // декрементируем все циклы команд в каретках и выполняет команду
        /****/
        src->curent_cycle++; // инкрементируем текущий цикл
        if ((src->curent_cycle % g_sec) == 0)
        {
            fill_screen(init, src);
            algo_event_managment(init);
        }
        /****/
    }
    /****/
    end_ncurses(init, src);
    /****/
    // победитель src->winer;
    if (src->fdump != -1 && src->fdump == (int)src->curent_cycle)
        dk_dump(src->field);
}
