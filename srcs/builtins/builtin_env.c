/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:22:38 by lportay           #+#    #+#             */
/*   Updated: 2018/04/01 14:07:46 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	get_new_argv(t_proc *p, char **av_addr)
{
	char **tmp;

	tmp = NULL;
	if (*p->argv)
	{
		tmp = ft_astr_dup(p->argv);
		ft_astr_nfree(p->argv, ft_astr_len(p->argv));
	}
	free(av_addr);
	if (tmp)
		p->argv = tmp;
	else
		p->argv = ft_astr_dup((char *[]){"printenv", NULL});
}

int		env_getopt(t_proc *p, int *getopt)
{
	if (!ft_strcmp("-i", *p->argv) || !ft_strcmp("-", *p->argv))
		return (env_i_opt(p));
	else if (!ft_strcmp("-u", *p->argv))
		return (env_u_opt(p));
	else if (!ft_strcmp("--", *p->argv))
		return (dash_opt(getopt));
	else
		return (env_invalid_opt(p));
}

int		err_getopt(t_proc *p, char **av_addr)
{
	p->type = BUILTIN;
	ft_astr_nfree(p->argv, ft_astr_len(p->argv));
	free(av_addr);
	p->argv = ft_astr_dup((char *[]){"env", NULL});
	return (-1);
}

int		ft_env(t_proc *p)
{
	char	*c;
	char	**av_addr;
	int		pmod;
	int		getopt;

	pmod = 0;
	getopt = 1;
	av_addr = p->argv;
	free(*p->argv++);
	while (*p->argv)
	{
		if ((**p->argv) == '-' && getopt)
		{
			if (env_getopt(p, &getopt) == -1)
				return (err_getopt(p, av_addr));
		}
		else if ((c = ft_strchr(*p->argv, '=')))
			pmod |= env_assignment(p, &getopt, c);
		else
			break ;
		free(*p->argv++);
	}
	get_new_argv(p, av_addr);
	return (pmod);
}
