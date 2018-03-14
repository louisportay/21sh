/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 19:20:03 by lportay           #+#    #+#             */
/*   Updated: 2018/03/13 19:24:40 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	reset_attributes(t_line *l)
{
	print_prompt();
	l->cursor_line = l->num_lines;
	l->offset_inline = l->prompt_len;
}

void	init_line(t_line *l)
{
	l->line = ft_dlstnew("HEAD", 4);
	l->lastline = l->line;
	reset_attributes(l);
}

/*
** When the line reader receives Ctrl-C
*/

void	reset_line(t_ctx *ctx, t_line *l)
{
	write(STDOUT_FILENO, "^C", 2);
	go_end(ctx, l);
	write(STDOUT_FILENO, "\n", 1);
	if (l->split_line)
		ft_dlstdel(&l->split_line, &delvoid);
	if (l->line)
		ft_dlsthead(&l->line);
	if (l->line && l->line != l->lastline)
	{
		ft_dlstdel(&l->line, &delvoid);
		ft_dlstdel(&l->lastline, &delvoid);
	}
	else
		ft_dlstdel(&l->lastline, &delvoid);
	stack_del(&l->linestate);
	stack_push(&l->linestate, stack_create(UNQUOTED));
	ft_strcpy(ctx->prompt_mode, PS1);
	init_line(l);
}
