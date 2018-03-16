/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:11:48 by lportay           #+#    #+#             */
/*   Updated: 2018/03/10 15:25:43 by lportay          ###   ########.fr       */
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
	{
	
	}
	else if (signum == SIGTSTP)
	{
	
	}
}

int		set_sighandler(void)
{
	signal(SIGWINCH, &sighandler); // Window size change
	signal(SIGTSTP, &sighandler);
	signal(SIGINT, &sighandler);
//	signal(SIGQUIT, &sighandler) == SIG_ERR) // "CTRL-\"
	signal(SIGTERM, &sighandler); // "kill"
	signal(SIGTTIN, SIG_IGN); // "kill"
	signal(SIGTTOU, SIG_IGN); // "kill"
	return (SUCCESS);
}
