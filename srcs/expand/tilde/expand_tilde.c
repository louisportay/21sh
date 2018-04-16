/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:18:07 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/11 15:34:21 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int		l_gethome(char *str, char **ret, t_ctx *ctx)
{
	char		*home;
	t_qbuf		*buf;

	if ((home = ft_astr_getval(ctx->environ, "HOME")) == NULL)
		return (0);
	buf = qbuf_new(1 << 8);
	qbuf_add(buf, home);
	qbuf_add(buf, str + 1);
	*ret = qbuf_del(&buf);
	return (1);
}

/*
**  + is $PWD
**  - is $OLDPWD
*/

static int		l_trysign(char *str, char **ret, t_ctx *ctx)
{
	t_qbuf		*buf;
	char		*s;

	buf = qbuf_new(1 << 8);
	if ((ft_strncmp(str, "~-", 2) == 0 || ft_strncmp(str, "~+", 2) == 0)
		&& (str[2] == '\0' || str[2] == '/'))
	{
		s = ft_astr_getval(ctx->environ, str[1] == '+' ? "PWD" : "OLDPWD");
		if (s == NULL)
		{
			qbuf_nuke(&buf);
			return (-1);
		}
		qbuf_add(buf, s);
		qbuf_add(buf, str + 2);
		*ret = qbuf_del(&buf);
		return (1);
	}
	qbuf_nuke(&buf);
	return (0);
}

static int		l_tryuser(char *str, char **ret)
{
	char		*usr;
	t_qbuf		*buf;

	usr = str + 1;
	buf = qbuf_new(1 << 8);
	qbuf_add(buf, USR_PATH);
	while (*usr != '\0' && *usr != '/')
	{
		qbuf_addc(buf, *usr);
		usr++;
	}
	if (access(buf->buffer, F_OK) == 0)
	{
		qbuf_add(buf, usr);
		*ret = qbuf_del(&buf);
		return (1);
	}
	qbuf_nuke(&buf);
	return (0);
}

/*
**  ADD NULL AND MALLOC ERRORS
*/

int				expand_tilde(char *str, char **ret, t_ctx *ctx)
{
	if (str == NULL)
		return (0);
	if (*str != '~')
		return (0);
	else if (str[1] == '/' || str[1] == '\0')
		return (l_gethome(str, ret, ctx));
	else if (l_trysign(str, ret, ctx) == 1)
		return (1);
	else if (l_tryuser(str, ret) == 1)
		return (1);
	return (0);
}
