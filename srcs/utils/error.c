/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 19:10:15 by lportay           #+#    #+#             */
/*   Updated: 2018/04/22 13:24:41 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
** Function which print the right error message
*/

void		dump_err(char errcode)
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
	else if (errcode == NOPROC)
		ft_putstr_fd(NOPROC_STR, STDERR_FILENO);
	else if (errcode == EFILEDESC)
		ft_putstr_fd(EFILEDESC_STR, STDERR_FILENO);
	else if (errcode == EWAITINTR)
		ft_putstr_fd(WAITINTR_STR, STDERR_FILENO);
	else if (errcode == EWAITCTX)
		ft_putstr_fd(WAITCTX_STR, STDERR_FILENO);
}

/*
** Print the error message and exit
*/

void		fatal_err(char errcode, t_ctx *ctx)
{
	signal(SIGINT, SIG_IGN);
	dump_err(errcode);
	wrap_exit(EXIT_FAILURE, ctx);
}

static void	free_hist(t_dlist **histlist, t_ctx *ctx)
{
	if ((*histlist)->next)
	{
		trim_history(&(*histlist)->next, ft_astr_getval(ctx->locals,
					"HISTFILESIZE"));
		save_history(ft_astr_getval(ctx->locals, "HISTFILE"),
				ft_dlstlast(*histlist), O_TRUNC, 1);
		*histlist = (*histlist)->next;
		ft_dlstdelone(&(*histlist)->prev, &delvoid);
		ft_dlstdel(histlist, &del_histentry);
	}
	else
		ft_dlstdelone(histlist, &delvoid);
}

static void	close_fds(t_ctx *ctx)
{
	close(ctx->std_fd[0]);
	close(ctx->std_fd[1]);
	close(ctx->std_fd[2]);
	tcsetpgrp(ctx->term_fd, ctx->pid);
	close(ctx->term_fd);
}

/*
** Free everything
*/

void		wrap_exit(int status, t_ctx *ctx)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &ctx->oldtios);
	if (ctx->istty)
		ft_putstr_fd("exit\n", ctx->std_fd[0]);
	if (ctx->line.line)
		ft_dlstdel(&ctx->line.line, &delvoid);
	if (ctx->yank)
		ft_dlstdel(&ctx->yank, &delvoid);
	if (ctx->line.linestate)
		stack_del(&ctx->line.linestate);
	if (ctx->hist.list)
		free_hist(&ctx->hist.list, ctx);
	if (ctx->path)
		ft_astr_clear(&ctx->path);
	if (ctx->hash)
		hash_free(&ctx->hash, &ft_memdel);
	if (ctx->environ)
		ft_astr_clear(&ctx->environ);
	if (ctx->locals)
		ft_astr_clear(&ctx->locals);
	ft_strdel(&ctx->last_argv);
	if (ctx->builtins != NULL)
		hash_free(&ctx->builtins, NULL);
	hash_free(&ctx->hash, &ft_memdel);
	close_fds(ctx);
	exit(status);
}
