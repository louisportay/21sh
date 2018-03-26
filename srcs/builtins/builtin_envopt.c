/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_envopt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:42:34 by lportay           #+#    #+#             */
/*   Updated: 2018/03/25 20:29:13 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		env_i_opt(t_proc *p)
{
	ft_astr_clear(&p->env);
	p->env = ft_astr_dup((char *[]){NULL});
	return (0);
}

int		env_u_opt(t_proc *p)
{
	int i;

	if (p->argv[1] == NULL)
	{
		ft_asprintf(&p->data.str,
	"221sh: env: option requires an argument -- 'u'\n");
		return (-1);
	}
	if (ft_strchr(p->argv[1], '='))
	{
		ft_asprintf(&p->data.str,
	"221sh: env: Cannot unset '%s': Invalid argument\n", p->argv[1]);
		return (-1);
	}
	i = ft_astr_getkey(p->env, p->argv[1], ft_strlen(p->argv[1]));
	if (i != -1)
		free(ft_astr_remove_at(&p->env, i));
	free(*p->argv++);
	return (0);
}

int		env_invalid_opt(t_proc *p)
{
	ft_asprintf(&p->data.str, "221sh: env: invalid option -- '%c'\n",
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
