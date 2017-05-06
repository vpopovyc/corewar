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

int     ft_is_empty_line(char *src)
{
    int i;
    
    i = 0;
    while (src[i])
    {
        if (!ft_isspace(src[i]))
            return (1);
        i++;
    }
    return (0);
}


/*
** незаконченно
*/

void    ft_write_comands(t_gamer *src, int i, char *tmp)
{
    char    **line;
    char    **arguments;
    t_label *point;
    
    int first;
    int second;
    int third;
    
    src->label = ft_add_label();
    point = src->label;
    while (get_next_line(src->fd, &tmp) > 0)
    {
        line = ft_strsplit(tmp, ' '); /// написать сплит по пробелам и табуляциям
        // разбить строку на лейбл, имя команди , аргументы
        free(tmp);
        i = 0;
        if (line[i] && ft_is_empty_line(line[i]) == 1)
        {
            if (i == 0 && line[i])
            {
                // создает новую метку
                if ((tmp = ft_find_label(line[i])))
                {
                    if (point->name)
                    {
                        point->next = ft_add_label();
                        point = point->next;
                    }
                    point->name = tmp;
                    i++;
                }
                else if (!point->name)
                    point->name = ft_strdup("empty");
            }
            if (line[i] && (tmp = ft_find_and_check_comand(line[i])))
            {
                // создет команду
                if (point->comand->name)
                {
                    point->comand->next = ft_add_comand();
                    point->comand = point->comand->next;
                }
                point->comand = ft_add_comand();
                point->comand->name = tmp;
            }
            arguments = ft_strsplit(line[i], SEPARATOR_CHAR);
            if (arguments)
            {
                first = ft_valid_comand_arguments(arguments[0], &point->comand->arg1);
                
            }
        }
        i = 0;
        while (line[i])
        {
            ft_strdel(&line[i]);
            i++;
        }
        free(line);
    }
}
