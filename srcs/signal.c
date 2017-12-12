/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:04:12 by lportay           #+#    #+#             */
/*   Updated: 2017/12/12 23:12:17 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Définir les comportements pour chaque signal
*/

void		sig_switch(int signum, t_21sh *envaddr)
{
	static t_21sh *env;

	if (signum == SIGWINCH)
	{
		ioctl(STDIN_FILENO, TIOCGWINSZ, &env->ws);
		//tputs(env->tc.cl, 1, &ft_putchar_stdin);//always work
		clear_line(env);//work like `bash'
		redraw_line(env);
	}
	if (envaddr != NULL)
		env = envaddr;
}

static void	sighandler(int signum)
{
	sig_switch(signum, NULL);
}

int		wrap_signal(void)
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
	return (SUCCESS);
}
