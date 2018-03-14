/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:53:49 by lportay           #+#    #+#             */
/*   Updated: 2018/03/14 13:33:37 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** These functions are designed to redraw part of the line,
** changing some attributes.
*/

void	print_line_attributes(t_ctx *ctx, t_line *l, t_dlist *list)
{
	while (list)
	{
		l->offset_inline++;
		write(STDOUT_FILENO, list->data, 1);
		if (*(char *)list->data == '\n')
		{
			l->offset_inline = 0;
			l->cursor_line++;
			l->num_lines++;
		}
		else if (!(l->offset_inline % ctx->ws.ws_col))
		{
			l->cursor_line++;
			l->num_lines++;
			tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
		}
		list = list->next;
	}
}

void	print_line(t_dlist *list)
{
	while (list)
	{
		write(STDOUT_FILENO, list->data, 1);
		list = list->next;
	}
}
