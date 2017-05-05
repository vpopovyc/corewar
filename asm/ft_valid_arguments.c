#include "byte_code_header.h"

/*
** return (T_DIR == 1, T_IND == 2, T_REG == 3, invalid == 0)
*/

char *ft_direct_arg(char *src, int i)
{
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
			res = 1;
		free(tmp);
	}
	else
	{
		i = 1;
		while (ft_isdigit(src[i]))
			i++;
		if (src[i] == '\0' && i != 1)
			res = 1;
	}
	return (...........)
}

char 	*ft_indirect_arg(char *src, int i)
{
	while (ft_isdigit(src[i]))
			i++;
	if (src[i] == '\0')
		res = 2;
	return (.............)
}


char 	*ft_reg_arg(char *src, int i)
{
	while (ft_isdigit(src[i]))
		i++;
	if (src[i] == '\0')
	{
		tmp = ft_strsub(src, 1, ft_strlen(src) - 1);
		i = ft_atoi(tmp);
		if (i >= 1 && i <= 16)
			res = 3;
		free(tmp);
	}

}

int		ft_valid_comand_arguments(char *src)
{
	int		res;
	int		i;
	char	*tmp;

	i = 0;
	res = 0;
	if (src[0] == DIRECT_CHAR)
	{
		ft_direct_arg(src, 0);
	}
	else if (ft_isdigit(src[0]))
	{
		ft_indirect_arg(src, 0);
	}
	else if (src[0] == 'r')
		ft_reg_arg(src, 1);		
	return (res);
}