/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:09:51 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/21 19:53:49 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_H
# define __STACK_H

# include "../../libft/includes/libft.h"

typedef struct				s_stack_elem
{
	struct s_stack_elem		*top_elem;
	struct s_stack_elem		*bot_elem;
	char					*label;
}							t_stack_elem;

typedef struct				s_stack
{
	struct s_stack_elem		*top_node;
	struct s_stack_elem		*bot_node;
}							t_stack;

/*
** stack.c
*/

void						stack_init(t_stack *stack);
void						push(t_stack *stack, char *label);
void						pop(t_stack *stack);
char						*top(t_stack stack);
int							stack_size(t_stack *stack);
/*
** queue.c
*/

char						isinstack(char *str, t_stack *stack);
void						enqueue(t_stack *stack, char *label);
void						dequeue(t_stack *stack);
char						*bot(t_stack stack);
#endif
