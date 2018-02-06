/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 11:26:07 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 16:41:50 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	stack_print(t_stack *stack, char *sep)
{
	while (stack)
	{
		ft_putnbr(stack->state);
		ft_putstr(sep);
		stack = stack->down;
	}
}
