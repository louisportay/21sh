/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:11:48 by lportay           #+#    #+#             */
/*   Updated: 2018/02/27 16:07:56 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Définit les comportements pour chaque signal
** SIGINT réaffiche le prompt et kill les process en cours
*/

static void	sighandler(int signum)
{
	t_ctx *ctx;
	
	ctx = get_ctxaddr(NULL);
	if (signum == SIGWINCH && ctx->line_edition)
	{
		ioctl(STDIN_FILENO, TIOCGWINSZ, &ctx->ws);
		if (ctx->cur_line)
		{
			update_line(ctx, ctx->cur_line);
			clear_line(ctx, ctx->cur_line);
			redraw_line(ctx, ctx->cur_line);
		}
	}
	else if (signum == SIGINT)
	{
	
	}
	else if (signum == SIGTSTP)
	{
	
	}
}

int		set_sighandler(void)
{
	if (signal(SIGWINCH, &sighandler) == SIG_ERR) // Window size change
		return (FAILSETSIGHDLR);
	if (signal(SIGTSTP, &sighandler) == SIG_ERR)
		return (FAILSETSIGHDLR);
	if (signal(SIGINT, &sighandler) == SIG_ERR)
		return (FAILSETSIGHDLR);
//	if (signal(SIGQUIT, &sighandler) == SIG_ERR) // "CTRL-\"
//		return (FAILSETSIGHDLR);
	if (signal(SIGTERM, &sighandler) == SIG_ERR) // "kill"
		return (FAILSETSIGHDLR);
	if (signal(SIGTTIN, SIG_IGN) == SIG_ERR) // "kill"
		return (FAILSETSIGHDLR);
	if (signal(SIGTTOU, SIG_IGN) == SIG_ERR) // "kill"
		return (FAILSETSIGHDLR);
	if (signal(SIGCHLD, &jc_signal) == SIG_ERR) // Child?
		return (FAILSETSIGHDLR);
	return (SUCCESS);
}
