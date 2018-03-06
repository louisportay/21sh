/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:53:49 by lportay           #+#    #+#             */
/*   Updated: 2018/02/07 18:34:24 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** These functions are designed to redraw part of the line,
** changing some attributes.
*/

void	print_line_cursor_len(t_line *l, t_dlist *list)
{
	while (list)
	{
		l->line_len++;
		l->cursor_offset++;
		write(STDOUT_FILENO, list->data, 1);
		list = list->next;
	}
}

void	print_line_cursor(t_line *l, t_dlist *list)
{
	while (list)
	{
		l->cursor_offset++;
		write(STDOUT_FILENO, list->data, 1);
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
