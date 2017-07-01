/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dissassemble_comands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 17:58:19 by rvolovik          #+#    #+#             */
/*   Updated: 2017/06/01 15:49:34 by rvolovik         ###   ########.fr       */
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

int			debyte_codebyte(char codebyte, char *args_debyte, char com_ind)
{
	char	arg;
	char	byte;
	int		len;
	int		ind;

	ind = (int)com_ind;
	len = 0;
	byte = (codebyte & FMASK) >> FIRSTARG;
	arg = byte == 3 ? T_IND : byte;
	len += count_bytes(arg, com_ind);
	if (arg && ((arg | g_op[ind].args[0]) == g_op[ind].args[0]))
		args_debyte[0] = arg;
	byte = (codebyte & SMASK) >> SECONDARG;
	arg = byte == 3 ? T_IND : byte;
	len += count_bytes(arg, com_ind);
	if (arg && ((arg | g_op[ind].args[1]) == g_op[ind].args[1]))
		args_debyte[1] = arg;
	byte = (codebyte & TMASK) >> THIRDARG;
	arg = byte == 3 ? T_IND : byte;
	len += count_bytes(arg, com_ind);
	if (arg && ((arg | g_op[ind].args[2]) == g_op[ind].args[2]))
		args_debyte[2] = arg;
	return (len);
}

char		**get_args(char *file, char com_ind, unsigned int *pos, int flen)
{
	char			**args;
	char			args_debyte[ARGSNUM];
	unsigned char	codebyte;
	int				i;
	int				len;

	i = -1;
	ft_bzero(args_debyte, ARGSNUM);
	args = (char**)ft_memalloc(sizeof(char*) * (ARGSNUM + 1));
	if (g_op[(int)com_ind].code_byte)
	{
		codebyte = (unsigned char)file[(*pos)++];
		len = debyte_codebyte(codebyte, args_debyte, com_ind);
		len + (int)*pos > flen ? ft_error(10) : 0;
		while (++i < ARGSNUM)
			args[i] = parse_args(args_debyte[i], file, pos, com_ind);
	}
	else
	{
		len = (!g_op[(int)com_ind].label_size) ? 4 : 2;
		len + (int)*pos > flen ? ft_error(10) : 0;
		args[0] = form_direct(file, pos, com_ind);
	}
	return (args);
}

t_comand	*get_new_com(t_comand *head, char *file, unsigned int *pos, int l)
{
	t_comand	*nw;
	t_comand	*ptr;

	nw = (t_comand*)ft_memalloc(sizeof(t_comand));
	nw->name = get_com_name(file, pos);
	nw->arg = get_args(file, nw->name, pos, l);
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
	while (pos <= data->file_len - 1)
	{
		data->comands_list = get_new_com(
			data->comands_list, data->file_data, &pos, (int)data->file_len);
	}
	if (pos - data->curent_position != data->len_comands_code)
		ft_error(10);
}
