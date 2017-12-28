/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 11:26:07 by lportay           #+#    #+#             */
/*   Updated: 2017/12/22 11:26:18 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	stack_print(t_stack *stack, char *sep)
{
	while (stack)
	{
		ft_putnbr(stack->state);
		ft_putstr(sep);
		stack = stack->down;
	}
}
