/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enqueue_labels.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:41:09 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/21 19:36:11 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ENQUEUE_LABELS_H
# define __ENQUEUE_LABELS_H

# include "byte_code_header.h"

# define EMPTYLINE 		""
# define UNSCR		 	'_'
# define MINUS 			1

extern char				g_flag;
extern int				g_label_byte;
extern int				g_line;

/*
** isspace()
*/

char					iscomment(char *sv);
char					*get_label(char *line);
char					*get_substring(char *line);
char					g_op_compare(char *command, t_command *new);
int						separ_delim(int c);

/*
** hash_labels.c
*/

void					dig_or_lab_val(t_stack *dir, char *arg,
												char *flag, char mark);
void					digit_validation(char *src);
void					label_validation(t_stack *dir, char *src);
void					get_args(char *reference, t_stack *dir,
												char opcode, t_command *new);
char					*check_argument(char *refarg, t_stack *dir,
												char opcode, int i);

/*
** enqueue_labels.c
*/

void					add_commands(t_hash *table,
												char *lbl, t_command *com);
t_command				*create_commands_elem(char *label,
												t_stack *dir, char *line);
void					line_analyse(t_stack *queue, t_stack *dir,
												t_hash *table, char *ln);
void					check_stack(t_stack *labels, t_hash *table);
t_stack					*enqueue_labels(t_stack *queue, t_hash *table,
												unsigned int *p_s);
#endif
