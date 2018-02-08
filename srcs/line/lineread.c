/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 18:33:51 by lportay           #+#    #+#             */
/*   Updated: 2018/02/07 18:32:03 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"


void	init_line(t_ctx *ctx, t_line *line, t_key *key, int *status)
{
	ft_bzero(key->buf, READLEN);
	key->i = 0;
	*status = READON;
	line->line = ft_dlstnew(ft_strdup("HEAD"));
	line->lastline = line->line;
	line->cursor_offset = 0;
	line->multiline = false;
	print_prompt(ctx);
	line->line_len = line->cursor_offset;
}

void		lineread(t_ctx *ctx, t_line *line)
{
	t_key	key;
	int		status;

	init_line(ctx, line, &key, &status);	
	
	tputs(ctx->tc.im, 1, &ft_putchar_stdin);
	while (status == READON)
	{
		if (read(STDIN_FILENO, &key.buf[key.i++], 1) == -1)
			status = READERROR;
		else
			status = user_input(ctx, line, &key);
	}
	tputs(ctx->tc.ei, 1, &ft_putchar_stdin);

	if (line->multiline == true)
		move_cursor_end_of_line(ctx, line);
	if (ctx->hist.list)
		ft_dlsthead(&ctx->hist.list);
	ft_dlsthead(&line->line);

	if (status == READERROR)
		fatal_err(FAILREAD, ctx);
	else if (status == EXITSHELL)
		wrap_exit(EXIT_SUCCESS, ctx);
	else if (status == ERR_QUOTE)
		return (err_quotes(line));

	if (ctx->heredoc_eof)
		query_hdocstate(line->line->next, &line->linestate, ctx->heredoc_eof);
	else
		query_linestate(line->line->next, &line->linestate);
	if (line->linestate->state != UNQUOTED)
	{
		ft_strcpy(ctx->prompt_mode, PS2);
		if ((line->cursor_offset % ctx->ws.ws_col))
			write(STDOUT_FILENO, "\n", 1);
	}
	else
		write(STDOUT_FILENO, "\n", 1);

	join_split_lines(line);

	if (ctx->history && line->split_line->next && line->linestate->state == UNQUOTED && !dlst_isblank(line->split_line->next) && !ctx->heredoc_eof)
	{
		add_histentry(ctx);
		line->line_saved = true;
	}

	if (line->linestate->state == UNQUOTED || line->linestate->state == SQUOTE || line->linestate->state == DQUOTE)
		ft_dlstaddend(line->split_line, (line->final_newline = ft_dlstnew(ft_strdup("\n"))));
}
