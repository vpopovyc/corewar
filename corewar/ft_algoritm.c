
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

void    ft_check_mem_cell(t_carriage *head, char *field)
{
    t_carriage *p;
    
    p = head;
    while (p)
    {
        if ((unsigned char)field[p->position] > 0 && (unsigned char)field[p->position] <= 16)
        {
            
            if (field[p->position] != 1 && field[p->position] != 9 && field[p->position] != 12 && field[p->position] != 15)
            {
                // если есть оп код проверить его
            }
        }
        else
            p->position = ((p->position - 1) != MEM_SIZE) ? (p->position + 1) : 0;
        p = p->next;
    }
    // проверить ячейку на соответсвие команде , если для команды есть кодирующий байт проверить его
    // присвоить в point->f адрес функции для выполнения команды
    // если ето не команда увеличить индекс каретки на поле на один
}

void    ft_increment_cycle(t_carriage *head)
{
    t_carriage *point;

    point = head;
    while (point)
    {
        if  (point->f)
            point->comand_cycle--; // если указатель на функцию не налл
        if (point->comand_cycle == 0)// что указатель на функцию не налл
        {
//            point->f(point->arg); // если point->comand_cycle == 0 выполнить команду
            point->comand_cycle = 0;
        }
        point = point->next;
    }
}

void ft_algoritm(t_corewar *src)
{
    while (!src->carriage || src->cycle_to_die == 0 || src->fdump == src->curent_cycle)
    {
        ft_check_mem_cell(src->carriage, src->game_field); // проверяем ячейку памяти на наличие команды если команды нет передвигаем коретку
        if (src->last_cycle_to_die == src->cycle_to_die) // проверяем можноли уменьшить cycle_To_die
        {
            src->carriage = ft_check_del_carriege(src->carriage); //проверить и удалить все каретки которые не сказали live
            ft_check_cycle_to_die(src, 0); // сброс cycle_to_die
        }
        else
            src->last_cycle_to_die++; // инкрементируем счетчик циклов к смерти
        ft_increment_cycle(src->carriage); // декрементируем все циклы команд в каретках и выполняет команду
        src->curent_cycle++; // инкрементируем текущий цикл
    }
    if (src->fdump != -1 && src->fdump == src->curent_cycle)
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




