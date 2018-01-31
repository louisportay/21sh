/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:18:07 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/13 17:37:14 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "ft_env.h"
#include "./expand_tilde.h"

static int		l_gethome(char **str, t_environ *env)
{
	char		*home;
	char		*s;
	t_membuf	buf;

	home = ft_env_get_value(env->env, ENV_HOME);
	if (home == NULL)
		return (1);
	s = *str + 1;
	ft_mb_init(&buf);
	ft_mb_add(&buf, home, ft_strlen(home));
	ft_mb_add(&buf, s, ft_strlen(s));
	ft_strdel(str);
	*str = ft_mb_fetch(&buf);
	return (1);
}

/*
**  + is $PWD
**  - is $OLDPWD
*/

static int		l_trysign(char **str, t_environ *env)
{
	t_membuf	buf;
	char		*s;

	ft_mb_init(&buf);
	if (ft_strncmp(*str, "~+/", 3) == 0 || ft_strncmp(*str, "~-/", 3) == 0)
	{
		s = ft_env_get_value(env->env, (*str)[1] == '+' ? ENV_PWD : ENV_OLDPWD);
		if (s == NULL)
			return (1);
		ft_mb_add(&buf, s, ft_strlen(s));
		ft_mb_add(&buf, *str + 2, ft_strlen(*str + 2));
		ft_strdel(str);
		*str = ft_mb_fetch(&buf);
		return (1);
	}
	return (0);
}

static int		l_tryuser(char **str)
{
	char		*usr;
	t_membuf	buf;

	usr = *str + 1;
	ft_mb_init(&buf);
	ft_mb_add(&buf, USR_PATH, ft_strlen(USR_PATH));
	while (*usr != '\0' && *usr != '/')
	{
		ft_mb_addc(&buf, *usr);
		usr++;
	}
	ft_mb_stash(&buf);
	if (access(buf.rem, F_OK) == 0)
	{
		ft_mb_add(&buf, usr, ft_strlen(usr));
		ft_strdel(str);
		*str = ft_mb_fetch(&buf);
		return (1);
	}
	ft_mb_clear(&buf);
	return (1);
}

/*
**  ADD NULL AND MALLOC ERRORS
*/

int				expand_tilde(char **str, t_environ *env)
{
	if (**str != '~')
		return (1);
	else if ((*str)[1] == '/' || (*str)[1] == '\0')
		return (l_gethome(str, env));
	else if (l_trysign(str, env) == 1)
		return (1);
	else if (l_tryuser(str) == 1)
		return (1);
	return (0);
}
