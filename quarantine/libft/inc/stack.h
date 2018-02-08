/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 11:19:07 by lportay           #+#    #+#             */
/*   Updated: 2017/12/28 10:17:15 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

/*
** This stack implementation is used to keep track of a recursive state
** (through an enum [int] generally)
*/

typedef struct		s_stack
{
	struct s_stack	*down;
	int				state;
}					t_stack;

t_stack	*stack_create(int state);
void	stack_push(t_stack **stack, t_stack *new);
void	stack_pop(t_stack **stack);
void	stack_del(t_stack **stack);
void	stack_print(t_stack *stack, char *sep);

#endif