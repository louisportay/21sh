/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:04:12 by lportay           #+#    #+#             */
/*   Updated: 2017/11/20 09:01:49 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Définir les comportements pour chaque signal
*/

void		sig_switch(int signum, t_21sh *env)
{
	static t_21sh *envaddr;

	(void)signum;//
	(void)envaddr;//

	if (env != NULL)
		envaddr = env;
}

static void	sighandler(int signum)
{
	sig_switch(signum, NULL);
}

int		wrap_signal(void)
{
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
