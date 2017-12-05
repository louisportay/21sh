/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:23:05 by lportay           #+#    #+#             */
/*   Updated: 2017/12/05 13:27:40 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	init_local(t_21sh *env)// peut etre utilise pour reset les variables locales
{
	t_hash *tmp;

	hashclear(env->localvar, &ft_memdel);
	if (!(tmp = hashcreate("PS1", "21sh$ ", 7)))
		return (NOMEM);
	hashinsert(env->localvar, tmp, 0, &ft_memdel);
	if (!(tmp = hashcreate("PS2", "> ", 7)))
		return (NOMEM);
	hashinsert(env->localvar, tmp, 0, &ft_memdel);
	if (!(tmp = hashcreate("PS4", "+ ", 7)))
		return (NOMEM);
	hashinsert(env->localvar, tmp, 0, &ft_memdel);
	if (get_histfile(env) == NOMEM)
		return (NOMEM);
	if (!(tmp = hashcreate("HISTSIZE", HISTSIZE, ft_strlen(HISTSIZE))))
		return (NOMEM);
	hashinsert(env->localvar, tmp, 0, &ft_memdel);
	if (!(tmp = hashcreate("HISTFILESIZE", HISTFILESIZE, ft_strlen(HISTFILESIZE))))
		return (NOMEM);
	hashinsert(env->localvar, tmp, 0, &ft_memdel);
	return (SUCCESS);
}

static int	init_env(t_21sh *env)
{
	char 	*tmp;

	if ((tmp = ft_getenv("SHLVL", env->environ)))
		if (!(tmp = ft_itoa(ft_atoi(tmp) + 1)))
			return (NOMEM);
	if (ft_setenv("SHLVL", (tmp) ? tmp: "1", 1, &env->environ) == -1)
	{
		ft_strdel(&tmp);
		return (FAILSETENV);
	}
	ft_strdel(&tmp);
	if ((tmp = getcwd(NULL, 0)) == NULL)
		return (NODIR);
	if (ft_setenv("PWD", tmp, 1, &env->environ) == -1)
	{
		ft_strdel(&tmp);
		return (FAILSETENV);
	}
	ft_strdel(&tmp);

	return (SUCCESS);
}

static void	init_termios(t_21sh *env)
{
	if (env->line_edition == true)
	{
		env->tios.c_lflag &= ~(ICANON | ECHO);
		env->tios.c_cc[VMIN] &= 1;
		env->tios.c_cc[VTIME] &= 0;
		env->tc.le = tgetstr("le", NULL);
		env->tc.nd = tgetstr("nd", NULL);	
		env->tc.im = tgetstr("im", NULL);
		env->tc.ei = tgetstr("ei", NULL);
		env->tc.dc = tgetstr("dc", NULL);
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &env->tios) == -1 ||
	!env->tc.le || !env->tc.nd || !env->tc.im || !env->tc.ei || !env->tc.dc)
			env->line_edition = false;	
	}
}

/*
** mettre les variables dans l'ordre dans lequel elles ont ete declarees
*/
//

static void	init_values(t_21sh *env)
{
	env->environ = NULL;
	env->line = NULL;
	env->line_edition = true;
	hashinit(env->localvar);
	env->history = true;
	env->histfile = 0;
	env->histlist = NULL;
	env->histindex = 1;
}

/*
** Changer la gestion de l'acquisition de ligne si pas de TERM -->passer en mode raw
*/

static int	init(t_21sh *env, char **environ)
{
	char	*tmp;
	int		ret;

	init_values(env);
	if (tcgetattr(STDIN_FILENO, &env->oldtios) == -1 || tcgetattr(STDIN_FILENO, &env->tios) == -1 ||
		(tmp = getenv("TERM")) == NULL || tgetent(NULL, tmp) == ERR)
		env->line_edition = false;
	init_termios(env);

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &env->ws) == -1)// changer peut etre ca en changeant la bool pour l edition de ligne
		return (NOWINDOW);

	if (wrap_signal() == FAILSETSIGHDLR)
		return (FAILSETSIGHDLR);
	if (!(env->environ = ft_copyenv(environ)))
		return (NOENVIRON);
	if ((ret = init_env(env)) != SUCCESS)
		return (ret);
	if ((ret = init_local(env)) != SUCCESS)
		return (ret);
	init_hist(env);
	sig_switch(0, env);
	return (SUCCESS);
}

void	vingtetunsh(char  **environ)
{
	t_21sh	env;
	char	ret;

	if ((ret = init(&env, environ)) != SUCCESS)
		fatal_err(ret, &env);

//	dump_history(env.histlist->next);

	if (env.line_edition == true)
		while (1)//
			lineread(&env);
//	else
//		while (1)
//			getrawline(&env);

	wrap_exit(EXIT_SUCCESS, &env);
}
