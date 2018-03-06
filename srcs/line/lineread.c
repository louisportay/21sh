/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 18:33:51 by lportay           #+#    #+#             */
/*   Updated: 2018/03/06 20:48:17 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"


void	init_line(t_ctx *ctx, t_line *l)
{
	l->line = ft_dlstnew("HEAD", 4);
	l->lastline = l->line;
	l->cursor_offset = 0;
//	l->multiline = false;
	print_prompt(ctx);
	l->line_len = l->cursor_offset;
}

void		lineread(t_ctx *ctx, t_line *l)
{
	t_key	key;
	int		status;

	ft_bzero(key.buf, READLEN);
	key.i = 0;
	status = READON;
	init_line(ctx, l);
	
	tputs(ctx->tc.im, 1, &ft_putchar_stdin);
	while (status == READON)
	{
		if (read(ctx->fd, &key.buf[key.i++], 1) == -1)
			status = READERROR;
		else
			status = user_input(ctx, l, &key);
	}
	tputs(ctx->tc.ei, 1, &ft_putchar_stdin);

//	if (l->multiline == true)
	go_end(ctx, l);
	//	move_cursor_end_of_line(ctx, l);
	if (ctx->hist.list)
		ft_dlsthead(&ctx->hist.list);
	ft_dlsthead(&l->line);

	if (status == READERROR && !l->heredoc)
		fatal_err(FAILREAD, ctx);
	else if (status == READERROR)//cheap code
		return (err_line(l, FAILREAD));
	else if (status == ERR_QUOTE)
		return (err_line(l, BADQUOTES));
	else if (status == EXITSHELL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		wrap_exit(EXIT_SUCCESS, ctx);
	}

	if (l->heredoc)
		query_hdocstate(l->line, &l->linestate, l->eohdoc);
	else
		query_linestate(l->line->next, &l->linestate);

	if (l->linestate->state != UNQUOTED)
	{
		ft_strcpy(ctx->prompt_mode, PS2);
		if (l->cursor_offset % ctx->ws.ws_col)
			write(STDOUT_FILENO, "\n", 1);
	}
	else
		write(STDOUT_FILENO, "\n", 1);

	join_split_lines(l);
	add_newline(l);
}
