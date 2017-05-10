#include "byte_code_header.h"

/*
 ** получаем первую строку двухмерного масива
 */
char    *ft_find_label(char *src)
{
    char    *res;
    int     i;
    
    res = NULL;
    if (src[ft_strlen(src) - 1] == LABEL_CHAR)
    {
        i = 0;
        while (src[i] != ':')
        {
            if (!(ft_strchr(LABEL_CHARS, src[i])))
                ft_error(9);
            i++;
        }
        res = ft_strsub(src, 0, ft_strlen(src) - 1);
    }
    return (res);
}

char    *ft_find_and_check_comand(char *src)
{
    char    *res;
    
    res = NULL;
    (!(ft_strcmp(src, LIVE))) ? (res = src) : 0;
    (!(ft_strcmp(src, LD))) ? (res = src) : 0;
    (!(ft_strcmp(src, ST))) ? (res = src) : 0;
    (!(ft_strcmp(src, ADD))) ? (res = src) : 0;
    (!(ft_strcmp(src, SUB))) ? (res = src) : 0;
    (!(ft_strcmp(src, AND))) ? (res = src) : 0;
    (!(ft_strcmp(src, OR))) ? (res = src) : 0;
    (!(ft_strcmp(src, XOR))) ? (res = src) : 0;
    (!(ft_strcmp(src, ZJMP))) ? (res = src) : 0;
    (!(ft_strcmp(src, LDI))) ? (res = src) : 0;
    (!(ft_strcmp(src, STI))) ? (res = src) : 0;
    (!(ft_strcmp(src, FORK))) ? (res = src) : 0;
    (!(ft_strcmp(src, LLD))) ? (res = src) : 0;
    (!(ft_strcmp(src, LLDI))) ? (res = src) : 0;
    (!(ft_strcmp(src, LFORK))) ? (res = src) : 0;
    (!(ft_strcmp(src, AFF))) ? (res = src) : 0;
    (res == NULL) ? ft_error(10) : 0;
    return (res);
}

/*
** незаконченно
*/

void    ft_free_two_dimensional_array(char **array)
{
    int i;
    
    i = 0;
    while (array[i])
    {
        ft_strdel(&array[i]);
        i++;
    }
    free(array);
}

//void    print(char **line)
//{
//    int i;
//    
//    i = 0;
//    while (line[i])
//    {
//        ft_putstr(line[i]);
//        ft_putstr("\n");
//        i++;
//    }
//}

t_comand    *ft_current(t_comand *src)
{
    t_comand *res;
    
    res = src;
    while (res->next)
        res = res->next;
    return (res);
}

t_comand    *ft_end(t_comand *src)
{
    t_comand *new;
    
    new = src;
    while (new->next)
        new = new->next;
    new->next = ft_add_comand();
    new = new->next;
    return (new);
}


void    ft_write_comands(t_gamer *src, int i, char *tmp)
{
    char            **line;
    t_label         *point;
    t_comand        *comand;
    
    src->label = ft_add_label();
    src->label->comand = ft_add_comand();
    point = src->label;
    while (get_next_line(src->fd, &tmp) > 0)
    {
        if (tmp && tmp[0] != '\0')
        {
            line = all_delims_split(tmp);
            free(tmp);
            if (line)
            {
                if (!ft_strcmp(line[0], NAME_CMD_STRING) || !ft_strcmp(line[0], COMMENT_CMD_STRING)) // если еще одно имя и комент игрока вывести ошибку
                    ft_error(6);
                if (line[0][0] == COMMENT_CHAR) // если коментарий пропустить
                    ft_free_two_dimensional_array(line);// функция очистки двухмерного масива
                else
                {
                    i = 0;
                    if (i == 0 && line[i]) // проверка на вхождение метки
                    {
                        if ((tmp = ft_find_label(line[i]))) // если метка найдена
                        {
                            if (point->name)
                            {
                                point->next = ft_add_label();
                                point = point->next;
                                point->comand = ft_add_comand();
                            }
                            point->name = tmp;
                            i++;
                        }
                        else if (!point->name)
                            point->name = ft_strdup("empty"); // если метки нет
                    }
                    if (line[i] && (tmp = ft_find_and_check_comand(line[i])))
                    {
                        if (point->comand->name != NULL)
                            comand = ft_end(point->comand);
                        else
                            comand = ft_current(point->comand);
                        comand->name = ft_strdup(tmp);
                        i++;
                    }
                    else
                        ft_error(10);
                    ft_find_arguments(comand, line, i, 0);
                    ft_free_two_dimensional_array(line);
//                    printf("%s|%hhx|%s|%s|%s\n", comand->name, comand->op_code, comand->arg1, comand->arg2, comand->arg3);
                }
            }
        }
    }
    printf("\n\n");
}
