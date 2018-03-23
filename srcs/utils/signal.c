/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:11:48 by lportay           #+#    #+#             */
/*   Updated: 2018/03/21 13:14:44 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Définit les comportements pour chaque signal
** SIGINT	==> Réaffiche le prompt ou kill les process en cours
** SIGWINCH ==> Window size change
** SIGTERM ==> Call wrap_exit ?
** SIGQUIT ==> Block it.
*/

static void	reset_line(t_ctx *ctx, t_line *l)
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

void		sighandler(int signum)
{
	t_ctx *ctx;

	ctx = get_ctxaddr();
	if (signum == SIGWINCH && ctx->line_edition)
	{
		ioctl(STDIN_FILENO, TIOCGWINSZ, &ctx->ws);
		if (ctx->cur_line)
		{
			clear_line(ctx, ctx->cur_line);
			redraw_line(ctx, ctx->cur_line);
		}
	}
	else if (signum == SIGINT)
		reset_line(ctx, ctx->cur_line);
	else if (signum == SIGTSTP)
		{}
}

int			set_sighandler(void)
{
	signal(SIGWINCH, &sighandler);
	signal(SIGTSTP, &sighandler);
	signal(SIGINT, &sighandler);
//	signal(SIGQUIT, &sighandler) // "CTRL-\"
	signal(SIGTERM, &sighandler);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, &jc_signal);
	return (SUCCESS);
}
