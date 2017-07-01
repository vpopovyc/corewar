/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:12:08 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/20 14:51:58 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/stack.h"

int				stack_size(t_stack *stack)
{
	int				len;
	t_stack_elem	*i;

	len = 0;
	i = stack->top_node;
	if (i != NULL)
	{
		++len;
		while (i != stack->bot_node)
		{
			++len;
			i = i->bot_elem;
		}
	}
	return (len);
}

char			*top(t_stack stack)
{
	return (stack.top_node->label);
}

void			pop(t_stack *stack)
{
	t_stack_elem *stack_elem_for_free;

	if (stack->top_node == NULL)
		return ;
	else
	{
		stack_elem_for_free = stack->top_node;
		stack->top_node = stack_elem_for_free->bot_elem;
		if (stack->top_node != NULL)
			stack->top_node->top_elem = NULL;
		free(stack_elem_for_free->label);
		free(stack_elem_for_free);
	}
}

void			push(t_stack *stack, char *label)
{
	t_stack_elem *new_elem;

	new_elem = (t_stack_elem*)malloc(sizeof(t_stack_elem));
	new_elem->label = ft_strdup(label);
	new_elem->top_elem = NULL;
	new_elem->bot_elem = NULL;
	if (stack->top_node == NULL)
	{
		stack->top_node = new_elem;
		stack->bot_node = new_elem;
	}
	else
	{
		stack->top_node->top_elem = new_elem;
		new_elem->bot_elem = stack->top_node;
		stack->top_node = new_elem;
	}
}

void			stack_init(t_stack *stack)
{
	stack->top_node = NULL;
	stack->bot_node = NULL;
}
