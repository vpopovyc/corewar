/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 14:47:30 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/21 20:27:51 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/stack.h"

char	isinstack(char *str, t_stack *stack)
{
	t_stack_elem	*i;

	i = stack->top_node;
	if (i != NULL)
	{
		while (i)
		{
			if (ft_strequ(i->label, str))
				return (1);
			i = i->bot_elem;
		}
	}
	return (0);
}

char	*bot(t_stack stack)
{
	if (stack.bot_node)
		return (stack.bot_node->label);
	return (NULL);
}

void	enqueue(t_stack *stack, char *label)
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
		stack->bot_node->bot_elem = new_elem;
		new_elem->top_elem = stack->bot_node;
		stack->bot_node = new_elem;
	}
}

void	dequeue(t_stack *stack)
{
	pop(stack);
}
