/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_labels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 17:03:05 by rvolovik          #+#    #+#             */
/*   Updated: 2017/06/05 14:27:16 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/enqueue_labels.h"

void		dig_or_lab_val(t_stack *dir, char *arg, char *flag, char mark)
{
	if (*arg == LABEL_CHAR)
		label_validation(dir, arg + 1);
	else
		digit_validation(arg);
	if (mark)
	{
		g_flag |= DIR_CODE;
		*flag |= T_DIR;
	}
	else
	{
		g_flag |= IND_CODE;
		*flag |= T_IND;
	}
}

char		*check_argument(char *refarg, t_stack *dir, char opcode, int i)
{
	char	*arg;
	char	flag;

	g_flag = 0;
	flag = 0;
	arg = ft_strtrim(refarg);
	if (*arg == 'r' && ft_atoi(arg + 1) < 100)
	{
		g_flag |= REG_CODE;
		flag |= T_REG;
	}
	else if (*arg == DIRECT_CHAR)
		dig_or_lab_val(dir, arg + 1, &flag, 1);
	else
		dig_or_lab_val(dir, arg, &flag, 0);
	if (g_op[(int)opcode - 1].args[i] != (g_op[(int)opcode - 1].args[i] | flag))
		ft_error(13, g_line);
	return (arg);
}

void		label_validation(t_stack *dir, char *src)
{
	char *ptr;

	ptr = src;
	if (*ptr == '\0')
		ft_error(11, g_line);
	while (*ptr)
	{
		if (!ft_isdigit(*ptr) && !(97 <= *ptr && *ptr <= 122) && *ptr != UNSCR)
			ft_error(11, g_line);
		++ptr;
	}
	if (!isinstack(src, dir))
		push(dir, src);
}

void		digit_validation(char *src)
{
	char *ptr;

	ptr = src;
	if (*ptr == '\0')
		ft_error(12, g_line);
	else if (ft_issign(*ptr) == MINUS)
		++ptr;
	while (*ptr)
	{
		if (!ft_isdigit(*ptr))
			ft_error(12, g_line);
		++ptr;
	}
}

void		get_args(char *reference, t_stack *dir, char opcode, t_command *new)
{
	int				i;
	char			**args;

	i = 0;
	reference += ft_strlen(g_op[(int)opcode - 1].name);
	args = all_delims_split(reference, separ_delim);
	while (i < g_op[(int)opcode - 1].num_args)
	{
		if (!args[i])
			ft_error(2, g_line);
		new->args[i] = check_argument(args[i], dir, opcode, i);
		if (g_op[(int)opcode - 1].code_byte)
			new->codebyte |= g_flag << (6 - 2 * i);
		new->bytes += command_length(new->opcode);
		i++;
	}
	if (new->codebyte)
		new->bytes += 1;
	if (args[i] != NULL)
		ft_error(2, g_line);
	ft_ppdel(&args);
}
