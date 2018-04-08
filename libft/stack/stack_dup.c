/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 17:28:26 by lportay           #+#    #+#             */
/*   Updated: 2018/04/08 17:30:58 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack *stack_dup(t_stack *stack)
{
	t_stack *dup;
	t_stack *ret;

	if (stack == NULL)
		return (NULL);
	dup = NULL;
	stack_push(&dup, stack_create(stack->state));	
	ret = dup;
	stack = stack->down;
	while (stack)
	{
		dup->down = stack_create(stack->state); 
		dup = dup->down;
		stack = stack->down;
	}
	return (ret);
}
