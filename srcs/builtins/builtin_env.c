/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:22:38 by lportay           #+#    #+#             */
/*   Updated: 2018/02/23 19:04:42 by lportay          ###   ########.fr       */
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

int		i_opt(t_proc *p)
{
	ft_astr_clear(&p->env);	
	p->env = ft_astr_dup((char *[]){NULL});
	return (0);
}

int		u_opt(t_proc *p)
{
	int i;

	if (p->argv[1] == NULL)
	{
		asprintf(&p->data.str,
	"221sh: env: option requires an argument -- 'u'\n");
		return (-1);
	}
	if (ft_strchr (p->argv[1], '='))
	{
		asprintf(&p->data.str,
	"221sh: env: Cannot unset '%s': Invalid argument\n", p->argv[1]);
		return (-1);
	}
	i = ft_astr_getkey(p->env, p->argv[1], ft_strlen(p->argv[1]));
	if (i != -1)
		free(ft_astr_remove_at(&p->env, i));
	free(*p->argv++);
	return (0);
}

int		invalid_opt(t_proc *p)
{
	asprintf(&p->data.str, "221sh: env: invalid option -- '%c'\n",
			p->argv[0][1]);
	return (-1);
}

int		env_assignment(t_proc *p, int *getopt, char *eq_pos)
{
	int i;

	*getopt = 0;
	if ((i = ft_astr_getkey(p->env, *p->argv, eq_pos - *p->argv)) != -1)
		ft_astr_replace(p->env, i, ft_strdup(*p->argv));
	else
		ft_astr_append(&p->env, ft_strdup(*p->argv));
	return (!ft_strncmp(*p->argv, "PATH=", 5) ? 1 : 0);
}

int		dash_opt(int *getopt)
{
	*getopt = 0;
	return (0);
}

int		env_getopt(t_proc *p, int *getopt)
{
	if (!ft_strcmp("-i", *p->argv) || !ft_strcmp("-", *p->argv))
		return (i_opt(p));
	else if (!ft_strcmp("-u", *p->argv))
		return (u_opt(p));
	else if (!ft_strcmp("--", *p->argv))
		return (dash_opt(getopt));
	else
		return (invalid_opt(p));
}

int		err_getopt(t_proc *p, char **av_addr)
{
	p->type = BU_STR;
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
			break;
		free(*p->argv++);
	}
	get_new_argv(p, av_addr);
	return (pmod);
}
