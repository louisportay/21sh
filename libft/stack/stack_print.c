/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 11:26:07 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 16:08:32 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "ft_stdio.h"

/*
** changer le proto et mettre un pointeur sur fonction pour dump le contenu
*/

void	stack_print(t_stack *stack, char *sep)
{
	while (stack)
	{
		ft_putnbr(stack->state);
		ft_putstr(sep);
		stack = stack->down;
	}
}
