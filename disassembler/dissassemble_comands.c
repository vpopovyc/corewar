/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dissassemble_comands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 17:58:19 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/31 20:49:11 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

char		get_com_name(char *file, unsigned int *pos)
{
	char	ind;

	ind = 0;
	ind |= file[*pos];
	(*pos)++;
	if (!g_op[ind - 1].name)
		ft_error(9);
	return ((char)(ind - 1));
}

void		debyte_codebyte(char codebyte, char *args_debyte, char com_ind)
{
	char	arg;
	char	byte;

	byte = (codebyte & FMASK) >> FIRSTARG;
	arg = byte == 3 ? T_IND : byte;
	if (arg && ((arg | g_op[com_ind].args[0]) == g_op[com_ind].args[0]))
		args_debyte[0] = arg;
	byte = (codebyte & SMASK) >> SECONDARG;
	arg = byte == 3 ? T_IND : byte;
	if (arg && ((arg | g_op[com_ind].args[1]) == g_op[com_ind].args[1]))
		args_debyte[1] = arg;
	byte = (codebyte & TMASK) >> THIRDARG;
	arg = byte == 3 ? T_IND : byte;
	if (arg && ((arg | g_op[com_ind].args[2]) == g_op[com_ind].args[2]))
		args_debyte[2] = arg;
}

char		**get_args(char *file, char com_ind, unsigned int *pos)
{
	char			**args;
	char			args_debyte[ARGSNUM];
	unsigned char	codebyte;
	int				i;

	codebyte = 0;
	i = 0;
	ft_bzero(args_debyte, ARGSNUM);
	args = (char**)ft_memalloc(sizeof(char*) * (ARGSNUM + 1));
	if (g_op[com_ind].code_byte)
	{
		codebyte = (unsigned char)file[(*pos)++];
		debyte_codebyte(codebyte, args_debyte, com_ind);
		while (i < ARGSNUM)
		{
			args[i] = parse_args(args_debyte[i], file, pos, com_ind);
			i++;
		}
	}
	else
		args[0] = form_direct(file, pos, com_ind);
	return (args);
}

t_comand	*get_new_com(t_comand *head, char *file, unsigned int *pos)
{
	t_comand	*nw;
	t_comand	*ptr;

	nw = (t_comand*)ft_memalloc(sizeof(t_comand));
	nw->name = get_com_name(file, pos);
	nw->arg = get_args(file, nw->name, pos);
	ptr = head;
	if (!head)
		head = nw;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = nw;
	}
	return (head);
}

void		dissassemble_comands(t_desasm *data)
{
	unsigned int	pos;

	pos = data->curent_position;
	while (pos + 1 < data->file_len)
	{
		data->comands_list = get_new_com(
			data->comands_list, data->file_data, &pos);
	}
	/** printf("%d  - %d == %d && != %d\n", pos, data->curent_position, pos - data->curent_position, data->len_comands_code);
	** if (pos - data->curent_position != data->len_comands_code)
	** 	ft_error(10);*/
}
