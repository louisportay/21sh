/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:53:49 by lportay           #+#    #+#             */
/*   Updated: 2018/01/26 14:30:14 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	print_line_cursor_len(t_21sh *env, t_dlist *list)
{
	while (list)
	{
		env->line.line_len++;
		env->line.cursor_offset++;
		write(STDOUT_FILENO, list->content, 1);
		list = list->next;
	}
}

void	print_line_cursor(t_21sh *env, t_dlist *list)
{
	while (list)
	{
		env->line.cursor_offset++;
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
