/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:11:48 by lportay           #+#    #+#             */
/*   Updated: 2018/03/20 19:25:49 by lportay          ###   ########.fr       */
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

void	sighandler(int signum)
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
		{}
	else if (signum == SIGTSTP)
		{}
}

int		set_sighandler(void)
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
