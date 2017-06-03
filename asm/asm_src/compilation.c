/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compilation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:31:30 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/21 22:58:55 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/compilation.h"

int	g_fd_cor;
int	g_carrige;
int g_line;

void	uint_compile(unsigned int n)
{
	char	n_tmp;
	char	i;

	i = (char)sizeof(unsigned int);
	while (i)
	{
		n_tmp = (unsigned char)(n >> (8 * (i - 1)));
		write(g_fd_cor, &n_tmp, 1);
		--i;
	}
}

void	print_label(char *arg, char label_size, t_hash *table)
{
	t_hash	*elem;
	int		distance;
	short	cast;
	char	forprint;

	cast = 0;
	elem = get_item(arg, table);
	distance = elem->bytes - g_carrige;
	if (label_size)
	{
		cast = (short)distance;
		forprint = (char)(cast >> 8);
		write(g_fd_cor, &forprint, 1);
		forprint = (char)(cast);
		write(g_fd_cor, &forprint, 1);
	}
	else
		uint_compile((unsigned int)distance);
}

void	print_command(t_command *com, t_hash *table)
{
	char	op_arg;

	write(g_fd_cor, &com->opcode, 1);
	if (com->codebyte)
	{
		write(g_fd_cor, &com->codebyte, 1);
		op_arg = (com->codebyte >> FIRSTARG) & C_TAKAYA_C;
		insert_args(op_arg, com->args[0], table, com->opcode);
		op_arg = (com->codebyte & SECONDARG) >> 4;
		insert_args(op_arg, com->args[1], table, com->opcode);
		op_arg = (com->codebyte & THIRDARG) >> 2;
		insert_args(op_arg, com->args[2], table, com->opcode);
	}
	else if (com->opcode)
		insert_direct(com->args[0],
			g_op[(int)com->opcode - 1].label_size, table);
	g_carrige += com->bytes;
}

void	labels_compile(t_hash *table, t_stack *q_labels)
{
	t_hash		*label;
	t_command	*command;

	while (q_labels->top_node && q_labels->bot_node)
	{
		label = get_item(top(*q_labels), table);
		dequeue(q_labels);
		command = label->commands;
		while (command)
		{
			print_command(command, table);
			command = command->next;
		}
	}
}

void	compilation(t_hash *tb, t_stack *q_lb, header_t *re, char *path)
{
	char	*cor_path;
	int		i;

	g_carrige = 0;
	cor_path = ft_strjoin(path, ".cor");
	g_fd_cor = open(cor_path, USER_RIGHTS);
	uint_compile(re->magic);
	i = 0;
	while (i < ALIGNED_PROGNAME)
		write(g_fd_cor, &(re->prog_name[i++]), 1);
	uint_compile(re->prog_size);
	i = 0;
	while (i < ALIGNED_COMMENT)
		write(g_fd_cor, &(re->comment[i++]), 1);
	labels_compile(tb, q_lb);
	close(g_fd_cor);
	free(cor_path);
}
