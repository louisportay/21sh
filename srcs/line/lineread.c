/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 18:33:51 by lportay           #+#    #+#             */
/*   Updated: 2018/03/31 13:31:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_input(t_ctx *ctx, t_key *key, t_line *l)
{
	int ret;

	if (read(ctx->std_fd[0], &key->buf[key->i++], 1) == -1)
		ret = READERROR;
	else
		ret = user_input(ctx, l, key);
	return (ret);
}

/*
**	history_expansion(&ctx->hist, l->line);
** after the dlsthead
*/

static void	cleanup_after_read(t_ctx *ctx, t_line *l)
{
	go_end(ctx, l);
	ft_dlsthead(&ctx->hist.list);
	ft_dlsthead(&l->line);
}

static void	special_read_status(t_ctx *ctx, t_line *l, int status)
{
	if (status == READERROR && !l->eohdoc)
		fatal_err(FAILREAD, ctx);
	else if (status == READERROR)
		err_line(l, FAILREAD);
	else if (status == ERR_QUOTE)
	{
		if (l->eohdoc)
			warning_heredoc(l);
		else
			err_line(l, BADQUOTES);
	}
	else if (status == EXITSHELL)
		wrap_exit(EXIT_SUCCESS, ctx);
}

static void	update_prompt(t_ctx *ctx, t_line *l)
{
	ft_strcpy(ctx->prompt_mode, PS2);
	if (l->offset_inline % ctx->ws.ws_col)
		write(STDOUT_FILENO, "\n", 1);
}

void		lineread(t_ctx *ctx, t_line *l)
{
	t_key	key;
	int		status;

	ft_bzero(key.buf, READLEN);
	key.i = 0;
	status = READON;
	init_line(l);
	if (l->linestate->state & BSLASH)
		stack_pop(&l->linestate);
	tputs(ctx->tc.im, 1, &ft_putchar_stdin);
	while (status == READON)
		status = get_input(ctx, &key, l);
	tputs(ctx->tc.ei, 1, &ft_putchar_stdin);
	if (!l->line && l->eohdoc)
	{
		ft_dlsthead(&ctx->hist.list);
		return ;
	}
	cleanup_after_read(ctx, l);
	if (status != FINISHREAD)
	{
		special_read_status(ctx, l, status);
		return ;
	}
	get_state(l);
	if (l->linestate->state != UNQUOTED)
		update_prompt(ctx, l);
	else
		write(STDOUT_FILENO, "\n", 1);
	join_split_lines(l);
	add_newline(l);
}
