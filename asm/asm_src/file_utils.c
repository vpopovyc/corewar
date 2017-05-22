/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:32:20 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/21 20:39:06 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/byte_code_header.h"
#include "../headers/enqueue_labels.h"

int g_fd_s;

int		command_length(char opcode)
{
	if (g_flag == REG_CODE)
		return ((int)1);
	else if (g_flag == IND_CODE)
		return ((int)2);
	else if (g_flag == DIR_CODE)
	{
		if (g_op[(int)opcode - 1].label_size)
			return ((int)2);
		else
			return ((int)4);
	}
	return ((int)0);
}

char	*obrezka_stroki(char *line)
{
	char	*tmp;
	char	*quote;

	quote = ft_strchr(line, LABEL_CHAR) + 1;
	tmp = ft_strdup(quote);
	return (tmp);
}

void	skip_spaces(char **line)
{
	while (isspace(**line))
		++(*line);
}

char	*filepath(char *str)
{
	char	*ptr;
	char	*dot;

	ptr = str;
	if (str[ft_strlen(str) - 1] != 's' && str[ft_strlen(str) - 1] != '.')
		ft_error(3);
	while (*ptr)
	{
		if (*ptr == '.')
			dot = ptr;
		ptr++;
	}
	return (ft_strsub(str, 0, dot - str));
}

char	*ft_open(char *path)
{
	char	s[2];

	if ((g_fd_s = open(path, O_RDONLY)) < 0)
		ft_error(3);
	if (read(g_fd_s, s, 0) < 0)
		ft_error(4);
	return (filepath(path));
}
