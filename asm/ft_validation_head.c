#include "header.h"

void	ft_next_line(t_gamer *src, int dest, int b, unsigned int len)
{
	char            *s;
	char            *del;
	char            *tmp;
	unsigned int    index;

    index = 0;
    tmp = NULL;
    while (b == 0 && get_next_line(src->fd, &tmp) > 0)
    {
        index = 0;
        len = 0;
        while (tmp[index] && tmp[index] != '"')
        {
           index++;
           len++;
        }
		(tmp[index] == '"') ? (b = 1) : 0;
        s = ft_strsub(tmp, index - len, len);
        s = ft_strjoin("\n", s);
        del = (dest == 0) ? src->name : src->comment;
        (dest == 0) ? (src->name = ft_strjoin(src->name, s)) : (src->comment = ft_strjoin(src->comment, s));
        free(del);
		if (s)
            free(s);
		if (b == 0)
			free(tmp);
    }
	(b != 1) ? ft_error(6) : 0;
	index++;
	while (tmp[index])
		(ft_isspace(tmp[index])) ? (index++) : ft_error(6);
}

void	ft_name(t_gamer *src, char *tmp, unsigned int index, unsigned int len)
{
	index = src->len_def_name;
	while (ft_isspace(tmp[index]))
		index++;
	(tmp[index] != '"') ? ft_error(6) : 0;
	index++;
	if (tmp[index] == '"')
		src->name = ft_strdup("");
	else
	{
		len = 0;
		while (tmp[index] && tmp[index] != '"')
		{
			index++;
			len++;
		}
		src->name = ft_strsub(tmp, index - len, len);
		(tmp[index] != '"') ? ft_next_line(src, 0, 0, 0) : 0;
	}
	index++;
	while (tmp[index])
		(ft_isspace(tmp[index])) ? (index++) : ft_error(6);
	free(tmp);
	src->header++;
}

void	ft_comment(t_gamer *src, char *tmp, unsigned int index, unsigned int len)
{
	(src->name == NULL) ? ft_error(6) : 0;
    index = src->len_def_comment;
    while (ft_isspace(tmp[index]))
        index++;
    (tmp[index] != '"') ? ft_error(6) : 0;
    index++;
    len = 0;
    while (tmp[index] && tmp[index] != '"')
    {
        index++;
        len++;
    }
    src->comment = ft_strsub(tmp, index - len, len);
    (tmp[index] != '"') ? ft_next_line(src, 1, 0, 0) : 0;
    index++;
    while (tmp[index])
        (ft_isspace(tmp[index])) ? (index++) : ft_error(6);
    free(tmp);
    src->header++;
}

void	ft_validation(t_gamer *new)
{
	char	*tmp;
	char	*del;

	new->len_def_name = ft_strlen(NAME_CMD_STRING);
	new->len_def_comment = ft_strlen(COMMENT_CMD_STRING);
	while (new->header != 2 && get_next_line(new->fd, &tmp) > 0)
	{
		del = tmp;
		while (ft_isspace(*tmp))
			tmp++;
		if (*tmp != COMMENT_CHAR && *tmp != '\0')
		{
			if (!(ft_strncmp(tmp, NAME_CMD_STRING, new->len_def_name)))
				ft_name(new, ft_strdup(tmp), 0, 0);
			else if (!(ft_strncmp(tmp, COMMENT_CMD_STRING, new->len_def_comment)))
				ft_comment(new, ft_strdup(tmp), 0, 0);
			free(del);
		}
	}
	(new->header != 2) ? ft_error(6) : 0;
	ft_putstr(new->name);
	ft_putstr("\n");
	ft_putstr(new->comment);
    ft_putstr("\n");
}

//подсчитать длину имени и комента
//почистить bzero





