/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 12:01:55 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/12 12:01:58 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

char	*ft_direct_arg(char *src, int i)
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
			res = ft_strdup(src);
	}
	else
	{
		i = (src[1] == '-') ? 2 : 1;
		while (ft_isdigit(src[i]))
			i++;
		if (src[i] == '\0' && i != 1)
			res = ft_strdup(src);
	}
	return (res);
}

char	*ft_indirect_arg(char *src, int i)
{
	char	*res;

	res = NULL;
    if (src[0] == LABEL_CHAR)
    {
        i = 1;
        while (src[i])
        {
            if (!ft_strchr(LABEL_CHARS, src[i]))
                return NULL;
            i++;
        }
        res = ft_strdup(src);
    }
    else
    {
        if (src[i] == '-')
            i++;
        while (ft_isdigit(src[i]))
            i++;
        if (src[i] == '\0')
            res = ft_strsub(src, 0, ft_strlen(src));
    }
	return (res);
}

char	*ft_reg_arg(char *src, int i)
{
	char	*res;
	char	*tmp;

	res = NULL;
	while (ft_isdigit(src[i]))
		i++;
	if (src[i] == '\0')
	{
		tmp = ft_strsub(src, 1, ft_strlen(src) - 1);
		i = ft_atoi(tmp);
		if (i >= 0 && i <= 16)
			res = ft_strdup(src);
	}
	return (res);
}

int		ft_valid_comand_arguments(char *src, char **arg)
{
	int		res;
	char	*comand;

	res = 0;
	comand = NULL;
	if (src[0] == DIRECT_CHAR)
	{
		if ((comand = ft_direct_arg(src, 0)))
			res = 2;
	}
	else if (ft_isdigit(src[0]) || src[0] == '-' || src[0] == LABEL_CHAR)
	{
		if ((comand = ft_indirect_arg(src, 0)))
			res = 3;
	}
	else if (src[0] == 'r')
	{
		if ((comand = ft_reg_arg(src, 1)))
			res = 1;
	}
	if (res == 0)
		ft_error(11);
	*arg = comand;
	return (res);
}


int ft_arg(t_comand *src, char **arguments, int index, int *n_arg)
{
    int j;
    char *tmp;
    
    j = 0;
    while (arguments[j])
    {
        n_arg[index] = ft_valid_comand_arguments(arguments[j++], &tmp);
        (index == 0) ? (src->arg1 = tmp) : 0;
        (index == 1) ? (src->arg2 = tmp) : 0;
        (index++ == 2) ? (src->arg3 = tmp) : 0;
    }
    return (index);
}

void	ft_find_arguments(t_comand *src, char **line, int i, int index)
{
    int     n_arg[3];
	char	**arguments;

	n_arg[0] = 0;
	n_arg[1] = 0;
	n_arg[2] = 0;
    while (line[i] != NULL)
	{
		arguments = ft_strsplit(line[i++], SEPARATOR_CHAR);
		if (arguments && arguments[0] && arguments[0][0] == COMMENT_CHAR)
        {
            ft_free_two_dimensional_array(arguments);
            break ;
        }
        else if (arguments)
            index = ft_arg(src, arguments, index, n_arg);
        (arguments && arguments[0]) ? ft_free_two_dimensional_array(arguments) : 0;
	}
	src->op_code = ft_arg_to_binary(n_arg[0], n_arg[1], n_arg[2]);
    ft_check_for_comand(src->name, (unsigned int)src->op_code);
}
