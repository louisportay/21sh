/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 19:10:15 by lportay           #+#    #+#             */
/*   Updated: 2018/03/18 17:34:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Function which print the right error message
*/

void	dump_err(char errcode)
{
	if (errcode == BADQUOTES)
		ft_putstr_fd(BADQUOTES_STR, STDERR_FILENO);
	else if (errcode == NOMEM)
		ft_putstr_fd(NOMEM_STR, STDERR_FILENO);
	else if (errcode == NODIR)
		ft_putstr_fd(NODIR_STR, STDERR_FILENO);
	else if (errcode == FAILREAD)
		ft_putstr_fd(FAILREAD_STR, STDERR_FILENO);
	else if (errcode == BADOPT_C)
		ft_putstr_fd(BADOPT_C_STR, STDERR_FILENO);
	else if (errcode == BADOPT_F)
		ft_putstr_fd(BADOPT_F_STR, STDERR_FILENO);
}

/*
** Print the error message and exit
*/

void		fatal_err(char errcode, t_ctx *ctx)
{
	dump_err(errcode);
	wrap_exit(EXIT_FAILURE, ctx);
}

/*
** Free everything
*/

void	wrap_exit(int status, t_ctx *ctx)
{
	if (ctx->fd == STDIN_FILENO)
		write(STDERR_FILENO, "exit\n", 5);
	if (ctx->line.line)
		ft_dlstdel(&ctx->line.line, &delvoid);
	if (ctx->line.yank)
		ft_dlstdel(&ctx->line.yank, &delvoid);
//	if (ctx->line.linestate)
//		stack_del(&ctx->line.linestate);

	if (ctx->hist.list)//faire une fonction dédiée
	{
		if (ctx->hist.list->next)
		{
			trim_history(&ctx->hist.list->next, ft_astr_getval(ctx->locals, "HISTFILESIZE"));
			save_history(ft_astr_getval(ctx->locals, "HISTFILE"), ft_dlstlast(ctx->hist.list), O_TRUNC);
			ctx->hist.list = ctx->hist.list->next;
			ft_dlstdelone(&ctx->hist.list->prev, &delvoid);
			ft_dlstdel(&ctx->hist.list, &del_histentry);
		}
		else
			ft_dlstdelone(&ctx->hist.list, &delvoid);
	}
	if (ctx->path)
		ft_astr_clear(&ctx->path);
	if (ctx->hash)
		hash_free(&ctx->hash, &ft_memdel);
	if (ctx->environ)
		ft_astr_clear(&ctx->environ);
	if (ctx->locals)
		ft_astr_clear(&ctx->locals);
	if (ctx->line_edition == true)
		tcsetattr(STDIN_FILENO, TCSADRAIN, &ctx->oldtios);	
	close(ctx->tty);
	exit(status);
}
