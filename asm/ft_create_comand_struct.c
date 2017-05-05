#include "byte_code_header.h"

void	ft_add_comand(t_comand *src)
{
	t_comand *new;

	if (!src)
	{
		(!(src = (t_comand*)malloc(sizeof(t_comand)))) ? ft_error(1) : 0;
		src->name = NULL;
		src->arg1 = NULL;
		src->arg2 = NULL;
		src->arg3 = NULL;
		src->hex_code = NULL;
		src->next = NULL;
	}
	else
	{
		new = src;
		while (new->next)
			new = new->next;
		(!(new->next = (t_comand*)malloc(sizeof(t_comand)))) ? ft_error(1) : 0;
		new->next->name = NULL;
		new->next->arg1 = NULL;
		new->next->arg2 = NULL;
		new->next->arg3 = NULL;
		new->next->hex_code = NULL;
		new->next->next = NULL;
	}
}

void	ft_add_label(t_gamer *src)
{
	t_label	*new;

	if (!src->label)
	{
		(!(src->label = (t_label*)malloc(sizeof(t_label)))) ? ft_error(1) : 0;
		src->label->name = NULL;
		src->label->comand = NULL;
		src->label->next = NULL;
	}
	else
	{
		new = src->label;
		while (new->next)
			new = new->next;
		(!(new->next = (t_comand*)malloc(sizeof(t_comand)))) ? ft_error(1) : 0;
		new->next->name = NULL;
		new->next->comand = NULL;
		new->next->next = NULL;
	}
}
