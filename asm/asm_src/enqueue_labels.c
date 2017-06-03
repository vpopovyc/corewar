/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enqueue_labels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:41:12 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/21 22:34:29 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/enqueue_labels.h"

char		g_flag;
int			g_label_byte;
int			g_line;

void		add_commands(t_hash *table, char *lbl, t_command *com)
{
	t_hash		*tmp;
	t_command	*ptr;

	if (!key_exist(lbl, table))
		add_key_hash(lbl, g_label_byte, table);
	tmp = get_item(lbl, table);
	ptr = tmp->commands;
	if (!tmp->commands)
		tmp->commands = com;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = com;
	}
	if (com)
		g_label_byte += com->bytes;
}

t_command	*create_commands_elem(char *label, t_stack *dir, char *line)
{
	t_command	*new;

	skip_spaces(&line);
	if (ft_strnequ(label, line,
		ft_strlen(label)) && line[ft_strlen(label)] == ':')
		line += ft_strlen(label) + 1;
	skip_spaces(&line);
	if (*line == '\0')
		return (NULL);
	else
	{
		new = (t_command*)ft_memalloc(sizeof(t_command));
		new->opcode = g_op_compare(get_substring(line), new);
		get_args(line, dir, new->opcode, new);
	}
	return (new);
}

void		line_analyse(t_stack *queue, t_stack *dir, t_hash *table, char *ln)
{
	char		**tmp;
	char		*label;
	t_command	*command;

	tmp = all_delims_split(ln, ft_isspace);
	if (tmp)
	{
		if ((label = get_label(*tmp)))
		{
			if (!isinstack(label, queue))
				enqueue(queue, label);
			else
				ln = obrezka_stroki(ln);
		}
		else if (!bot(*queue))
			enqueue(queue, "empty");
		command = create_commands_elem(bot(*queue), dir, ln);
		add_commands(table, bot(*queue), command);
		ft_ppdel(&tmp);
		free(label);
	}
}

void		check_stack(t_stack *labels, t_hash *table)
{
	while (stack_size(labels))
	{
		if (!key_exist(top(*labels), table))
			ft_error(14, g_line);
		pop(labels);
	}
}

t_stack		*enqueue_labels(t_stack *queue, t_hash *table, unsigned int *p_s)
{
	char		*line;
	t_stack		dir;

	stack_init(&dir);
	g_label_byte = 0;
	g_flag = 0;
	g_line = 0;
	while (get_next_line(g_fd_s, &line) > 0 && ++g_line)
	{
		if (ft_strcmp(line, EMPTYLINE) && !iscomment(line))
			line_analyse(queue, &dir, table, line);
		free(line);
	}
	check_new_line(g_fd_s);
	check_stack(&dir, table);
	*p_s = g_label_byte;
	return (queue);
}
