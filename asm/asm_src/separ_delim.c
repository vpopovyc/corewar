/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separ_delim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 16:56:58 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/21 17:53:01 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/enqueue_labels.h"

char	iscomment(char *sv)
{
	skip_spaces(&sv);
	if (*sv == COMMENT_CHAR)
		return (1);
	else
		return (0);
}

char	*get_label(char *line)
{
	char	*ptr;

	skip_spaces(&line);
	ptr = line;
	while (*ptr)
	{
		if (*ptr == LABEL_CHAR)
			return (ft_strsub(line, 0, ptr - line));
		if (!ft_isdigit(*ptr) && !(97 <= *ptr && *ptr <= 122) && *ptr != UNSCR)
			break ;
		ptr++;
	}
	if (*ptr != '\0')
		ft_error(9, g_line);
	return (NULL);
}

char	*get_substring(char *line)
{
	char	*ptr;

	ptr = line;
	while (*ptr && !ft_isspace(*ptr))
		ptr++;
	return (ft_strsub(line, 0, ptr - line));
}

char	g_op_compare(char *command, t_command *new)
{
	int		i;

	i = 0;
	while (g_op[i].name)
	{
		if (ft_strequ(command, g_op[i].name))
		{
			free(command);
			new->bytes += 1;
			return (i + 1);
		}
		i++;
	}
	ft_error(10, g_line);
	return (-1);
}

int		separ_delim(int c)
{
	if (c == SEPARATOR_CHAR)
		return (1);
	else
		return (0);
}
