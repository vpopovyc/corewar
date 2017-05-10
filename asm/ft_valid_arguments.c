#include "byte_code_header.h"

char    *ft_direct_arg(char *src, int i)
{
    char *res;
    char *tmp;

    res = NULL;
	if (src[1] == LABEL_CHAR)
	{
		tmp = ft_strsub(src, 2, ft_strlen(src) - 2);
		while (tmp[i])
		{
			if (!ft_strchr(LABEL_CHARS, tmp[i]))
				break ;
			i++;
		}
		if (tmp[i] == '\0' && i != 0)
            res = tmp;
	}
	else
	{
        i = (src[1] == '-') ? 2 : 1;
		while (ft_isdigit(src[i]))
			i++;
		if (src[i] == '\0' && i != 1)
            res = ft_strsub(src, 1, ft_strlen(src) - 1);
	}
    return (res);
}

char 	*ft_indirect_arg(char *src, int i)
{
    char    *res;
    
    res = NULL;
    if (src[i] == '-')
        i++;
	while (ft_isdigit(src[i]))
			i++;
	if (src[i] == '\0')
		res = ft_strsub(src, 0, ft_strlen(src));
    return (res);
}

char 	*ft_reg_arg(char *src, int i)
{
    char *res;
    char *tmp;
    
    res = NULL;
	while (ft_isdigit(src[i]))
		i++;
	if (src[i] == '\0')
	{
		tmp = ft_strsub(src, 1, ft_strlen(src) - 1);
		i = ft_atoi(tmp);
		if (i >= 1 && i <= 16)
            res = tmp;;
	}
    return (res);
}

/*
** возвращает тип аргумента (T_DIR == 2, T_IND == 3, T_REG == 1, invalid == 0)
** записывает аргумент в строку по адресу **arg, если невалидный аргумент arg == NULL
*/

int		ft_valid_comand_arguments(char *src, char **arg)
{
	int		res;
    char    *comand;

	res = 0;
    comand = NULL;
	if (src[0] == DIRECT_CHAR)
        ((comand = ft_direct_arg(src, 0)) != NULL) ? (res = 2) : 0;
	else if (ft_isdigit(src[0]) || src[0] == '-')
        ((comand = ft_indirect_arg(src, 0)) != NULL) ? (res = 3) : 0;
	else if (src[0] == 'r')
        ((comand = ft_reg_arg(src, 1)) != NULL) ? (res = 1) : 0;
    if (res == 0)
        ft_error(11);
    *arg = comand;
	return (res);
}

char        arg_to_binary(char b1, char b2, char b3)
{
    char byte;
    
    byte = 0;
    byte |= b3 << 2;
    byte |= b2 << 4;
    byte |= b1 << 6;
    return (byte);
}

void    ft_find_arguments(t_comand *src, char **line, int i, int index)
{
    int     j;
    int     n_arg[3];
    char    **arguments;
    char    *tmp;
    
    n_arg[0] = 0;
    n_arg[1] = 0;
    n_arg[2] = 0;
    while (line[i] != NULL)
    {
        if ((arguments = ft_strsplit(line[i++], SEPARATOR_CHAR)))
        {
            j = 0;
            while (arguments[j])
            {
                (index > 2) ? ft_error(11) : 0;
                n_arg[index] = ft_valid_comand_arguments(arguments[j++], &tmp);
                (index == 0) ? (src->arg1 = tmp) : 0;
                (index == 1) ? (src->arg2 = tmp) : 0;
                (index++ == 2) ? (src->arg3 = tmp) : 0;
            }
            ft_free_two_dimensional_array(arguments);
        }
    }
    src->op_code = arg_to_binary((char)n_arg[0], (char)n_arg[1], (char)n_arg[2]);
}
