/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 17:38:03 by rvolovik          #+#    #+#             */
/*   Updated: 2017/06/01 15:08:22 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

char	*form_registry(char *file, unsigned int *pos)
{
	int		regnum;
	char	*tmp;
	char	*ret;

	regnum = (int)file[(*pos)++];
	tmp = ft_itoa(regnum);
	ret = ft_strjoin(REGCHAR, tmp);
	free(tmp);
	return (ret);
}

char	*form_direct(char *file, unsigned int *pos, int com_ind)
{
	int		res;
	char	*tmp;
	char	*ret;

	res = 0;
	if (!g_op[com_ind].label_size)
		res = (int)write_to_int(file, pos);
	else
		res = (int)write_to_short(file, pos);
	tmp = ft_itoa(res);
	ret = ft_strjoin(DIRCHAR, tmp);
	free(tmp);
	return (ret);
}

char	*form_indirect(char *file, unsigned int *pos)
{
	int		res;
	char	*ret;

	res = write_to_short(file, pos);
	ret = ft_itoa(res);
	return (ret);
}

char	*parse_args(char t_arg, char *file, unsigned int *pos, int com_ind)
{
	if (t_arg)
	{
		if (t_arg == T_REG)
			return (form_registry(file, pos));
		else if (t_arg == T_DIR)
			return (form_direct(file, pos, com_ind));
		else if (t_arg == T_IND)
			return (form_indirect(file, pos));
	}
	return (NULL);
}
