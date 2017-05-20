
#include "corewar.h"

void    ft_check_cycle_to_die(t_corewar *src, int n_live)
{
    t_carriage  *p;

    p = src->carriage;
    while (p)
    {
        (p->live_in_cycle > n_live) ? (n_live = p->live_in_cycle) : 0;
        if (n_live >= NBR_LIVE)
            break ;
        p = p->next;
    }
    if (n_live >= NBR_LIVE || src->n_check == MAX_CHECKS)
    {
        src->n_check = 0;
        src->cycle_to_die -= CYCLE_DELTA;
    }
    else
        src->n_check++;
    src->last_cycle_to_die = 0;
}



void    ft_check_mem_cell(t_carriage *head, char *field)
{
    t_carriage *p;
    
    p = head;
    while (p)
    {
        if ((unsigned char)field[p->posinion] > 0 && (unsigned char)field[p->posinion] <= 16)
        {
            
        }
        else
            p->posinion = ((p->posinion - 1) != MEM_SIZE) ? (p->posinion + 1) : 0;
        p = p->next;
    }
    // проверить ячейку на соответсвие команде
    // присвоить в point->f адрес функции для выполнения команды
    // если ето не команда увеличить индекс каретки на поле на один
}

void    ft_increment_cycle(t_carriage *head, t_corewar *src)
{
    t_carriage *point;
    
    point = head;
    while (point)
    {
        point->comand_cycle--;
        if (point->comand_cycle == 0)
            point->f(point->arg); // если point->comand_cycle == 0 выполнить команду
        point = point->next;
    }
}

void ft_algoritm(t_corewar *src)
{
    t_carriage *point;
    
    while (!src->carriage || src->cycle_to_die == 0 || src->fdump == src->curent_cycle)
    {
        point = src->carriage;
        while (point) // проверяем ячейку памяти на наличие команды если команды нет передвигаем коретку
        {
            ft_check_mem_cell(point, src->game_field);
            point = point->next;
        }
        ft_increment_cycle(src->carriage, src); // декрементируем все циклы команд в каретках
        if (src->last_cycle_to_die == src->cycle_to_die) // проверяем можноли уменьшить cycle_To_die
        {
            ft_check_cycle_to_die(src, 0);
            src->carriage = ft_check_del_carriege(src->carriage); //проверить и удалить все каретки которые не сказали live
        }
        else
            src->last_cycle_to_die++;
        src->curent_cycle++; // инкрементируем текущий цикл
        src->last_cycle_to_die++; // инкрементируем счетчик циклов к смерти
    }
    if (src->fdump != -1)
    {
        //остановиться после src->fdamp и вивести дамп
        if (src->verbose != -1)
        {
            // отрисовать визуально
        }
        else
        {
            // обычный вывод
        }
    }
}


// нужны 16 функций отвечающих за выполнения команд !!!!!!!!!!!!
// при выполнении команды передвигать каретку на байт следующий за командой и аргументами байт
// в функции live инкрементировать счетчик соответсвующего игрока

