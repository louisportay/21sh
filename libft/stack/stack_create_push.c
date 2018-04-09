/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 09:55:44 by lportay           #+#    #+#             */
/*   Updated: 2018/04/09 09:56:38 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int	stack_create_push(t_stack **stack, int new_state)
{
	t_stack *new;

	if ((new = stack_create(new_state)) == NULL)
		return (-1);
	stack_push(stack, new);	
	return (0);
}
