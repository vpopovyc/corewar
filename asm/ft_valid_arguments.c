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
		i = 1;
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
	while (ft_isdigit(src[i]))
			i++;
	if (src[i] == '\0')
		res = ft_strsub(src, 1, ft_strlen(src));
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
** возвращает тип аргумента (T_DIR == 1, T_IND == 2, T_REG == 3, invalid == 0)
** записывает аргумент в строку по адресу **arg, если невалидный аргумент arg == NULL
*/
int		ft_valid_comand_arguments(char *src, char **arg)
{
	int		res;
    char    *tmp;
    char    *comand;

	res = 0;
    comand = NULL;
//    if (src[ft_strlen(src) - 1] == SEPARATOR_CHAR)
//        ft_strsub(src, 0, ft_strlen(src) - 2);
//    else
        tmp = src;
	if (tmp[0] == DIRECT_CHAR)
        ((comand = ft_direct_arg(tmp, 0)) != NULL) ? (res = 1) : 0;
	else if (ft_isdigit(tmp[0]))
        ((comand = ft_indirect_arg(tmp, 1)) != NULL) ? (res = 2) : 0;
	else if (tmp[0] == 'r')
        ((comand = ft_reg_arg(tmp, 0)) != NULL) ? (res = 3) : 0;
    if (tmp == 0)
        ft_error(11);
    *arg = comand;
	return (res);
}
