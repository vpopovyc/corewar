/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 16:28:45 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/15 15:32:21 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

// void printlabel(t_label *head)
// {
// 	t_label		*label;
// 	t_comand	*comand;
//
// 	label = head;
// 	while (label)
// 	{
// 		printf("%s:\n", label->name);
// 		comand = label->comand;
// 		while (comand)
// 		{
// 			printf("%s %s %s %s\n", comand->name, comand->arg1, comand->arg2, comand->arg3);
// 			comand = comand->next;
// 		}
// 		printf("\n");
// 		label = label->next;
// 	}
// }
// static void			push_command(char *label, t_comand *new, t_label *head)
// {
// 	t_label		*ptr_lab;
// 	t_comand	*ptr_com;
//
// 	ptr_lab = head;
// 	while (ptr_lab)
// 	{
// 		if (ft_strequ(label, ptr_lab->name))
// 			break ;
// 		ptr_lab = ptr_lab->next;
// 	}
// 	ptr_com = ptr_lab->comand;
// 	if (!ptr_com)
// 		ptr_com = new;
// 	else
// 	{
// 		while (ptr_com->next)
// 			ptr_com = ptr_com->next;
// 		ptr_com->next = new;
// 	}
// }
// static t_comand    *ft_addcomand(char *name, char *arg1, char *arg2, char *arg3, char opcode)
// {
// 	t_comand *new;
//
//     new = (t_comand*)malloc(sizeof(t_comand));
//     new->name = ft_strdup(name);
//     new->arg1 = ft_strdup(arg1);
//     new->arg2 = ft_strdup(arg2);
//     new->arg3 = ft_strdup(arg3);
//     new->hex_code = opcode;
//     new->next = NULL;
//     return (new);
// }
// static t_label     *ft_addlabel(t_label *head, char *name, t_comand *comand)
// {
// 	t_label	*new;
// 	t_label	*ptr;
//
//     new = (t_label*)malloc(sizeof(t_label));
//     new->name = ft_strdup(name);
//     new->comand = comand;
//     new->next = NULL;
// 	ptr = head;
// 	if (!head)
// 		head = new;
// 	else
// 	{
// 		while (ptr->next)
// 			ptr = ptr->next;
// 		ptr->next = new;
// 	}
//     return (head);
// }
// void fill_label_list(t_label **head)
// {
// 	// (*head) = ft_addlabel(*head, "command", ft_addcomand("\0", "\0", "\0", "\0", 0));
// 	(*head) = ft_addlabel(*head, "l2", ft_addcomand("sti", "r1", "%:live", "%1", 0x68));
// 	push_command("l2", ft_addcomand("and",  "r1", "%0", "r1", 0x64), *head);
// 	(*head) = ft_addlabel(*head, "live", ft_addcomand("live", "%1", "\0", "\0", 0x80));
// 	push_command("live", ft_addcomand("zjmp",  "%:live", "\0", "\0", 0x80), *head);
// 	// (*head) = ft_addlabel(*head, "empty", ft_addcomand("\0", "\0", "\0", "\0", 0));
// }
/*
**	volosataya_podmyshka returns byte size of argument, invocates jajco_japonki()
*/
static int		volosataya_podmyshka(char hex_code, char label_size)
{
	if (hex_code == 1)
		return (1);
	else if (hex_code == 3)
		return (2);
	else if (hex_code == 2)
		return (label_size ? 2 : 4);
	return (0);
}
/*
**	returns number of bytes reserved by command
*/
static int		jajco_japonki(t_comand *comand)//заносить опкод в имя команды
{
	int			i;
	int			n;

	n = 0;
	i = 0;
	while (g_op[i].name)
	{
		if (ft_strequ(comand->name, g_op[i].name))
		{
			++n;
			break ;
		}
		i++;
	}
	if (g_op[i].code_byte)
	{
		n++;
		n += volosataya_podmyshka((comand->hex_code >> 6) & 3, g_op[i].label_size);
		n += volosataya_podmyshka((comand->hex_code & SECONDARG) >> 4, g_op[i].label_size);
		n += volosataya_podmyshka((comand->hex_code & THIRDARG) >> 2, g_op[i].label_size);
	}
	else if (g_op[i].op_code)
		n += g_op[i].op_code == 1 ? 4 : 2;
	return (n);
}
/*
**	returns number of bytes should be reserved by label
*/
static int		num_bytes(t_label *node)
{
	t_comand	*comand;
	int		n;

	n = 0;
	comand = node->comand;
	if (!node->comand)
		return (0);
	while (comand)
	{
		n += jajco_japonki(comand);
		comand = comand->next;
	}
	return (n);
}
/*
**	fills hash table with keys and bytes len of label
*/
void 	fill_hash_table(t_gamer *root, char *filename)
{
	t_label		*label;
	int			i;
	char		*tmp;

	i = 0;
	label = root->label;
	printf("file %s\n", filename);
	while (label)
	{
		add_key_hash(label->name, i, root->table);
		i += num_bytes(label);
		label = label->next;
	}
	tmp = ft_strjoin(filename, ".cor");
	printf("[%s]\n", tmp);
	header_uint_bc(root->header_bc->prog_size, i);
	step_to_byte_code(root->table, root->label, root->header_bc, open(tmp, O_CREAT | O_RDWR | O_TRUNC, S_IRWXG | S_IRWXO | S_IRWXU));
	free(filename);
	free(tmp);
}
