/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:53:49 by lportay           #+#    #+#             */
/*   Updated: 2017/12/19 16:56:57 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	print_line_cursor_len(t_21sh *env, t_dlist *list)
{
	while (list)
	{
		env->line_len++;
		env->cursor_offset++;
		write(STDOUT_FILENO, list->content, 1);
		list = list->next;
	}
}

void	print_line_cursor(t_21sh *env, t_dlist *list)
{
	while (list)
	{
		env->cursor_offset++;
		write(STDOUT_FILENO, list->content, 1);
		list = list->next;
	}
}

void	print_line(t_dlist *list)
{
	while (list)
	{
		write(STDOUT_FILENO, list->content, 1);
		list = list->next;
	}
}
