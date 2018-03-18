/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 18:33:51 by lportay           #+#    #+#             */
/*   Updated: 2018/03/18 18:16:57 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_input(t_ctx *ctx, t_key *key, t_line *l)
{
	if (read(ctx->fd, &key->buf[key->i++], 1) == -1)
		return (READERROR);
	else
		return (user_input(ctx, l, key));
}

static void	cleanup_after_read(t_ctx *ctx, t_line *l)
{
	if (l->line)
	{
		go_end(ctx, l);
		if (*(char *)l->line->data != '\\')
			ft_dlstinsert(l->line, ft_dlstnew("\n", 1));
		ft_dlsthead(&l->line);
	}
	ft_dlsthead(&ctx->hist.list);
//	history_expansion(&ctx->hist, l->line);
}

void	err_line(t_line *l, int errno)
{
	write(STDIN_FILENO, "\n", 1);
	dump_err(errno);
//	ft_dlstdel(&l->split_line, &delvoid);
	ft_dlstdel(&l->line, &delvoid);
//	stack_push(&l->linestate, stack_create(ERROR));
}

static void	read_err(t_ctx *ctx, t_line *l)
{
		if (l->eohdoc)
			err_line(l, FAILREAD);
		else
			fatal_err(FAILREAD, ctx);
//	else if (status == ERR_QUOTE)
//		err_line(l, BADQUOTES);
//	else if (status == EXITSHELL)
//	{
//		write(STDERR_FILENO, "exit\n", 5);
//		wrap_exit(EXIT_SUCCESS, ctx);
//	}
}

//static void	update_prompt(t_ctx *ctx, t_line *l)
//{
//	ft_strcpy(ctx->prompt_mode, PS2);
//	if (l->offset_inline % ctx->ws.ws_col)
//		write(STDOUT_FILENO, "\n", 1);
//}

void		lineread(t_ctx *ctx, t_line *l)
{
	t_key	key;
	int		status;

	ft_bzero(key.buf, READLEN);
	key.i = 0;
	status = READON;
	init_line(l);
	tputs(ctx->tc.im, 1, &ft_putchar_stdin);
	while (status == READON)
		status = get_input(ctx, &key, l);
	tputs(ctx->tc.ei, 1, &ft_putchar_stdin);
	cleanup_after_read(ctx, l);
	if (status == READERROR)
	{
		read_err(ctx, l);
		return ;
	}

//	get_state(l);
//	if (l->linestate->state != UNQUOTED)
//		update_prompt(ctx, l);
//	else
//	write(STDOUT_FILENO, "\n", 1); 
//	join_split_lines(l);
//	add_newline(l);
}
