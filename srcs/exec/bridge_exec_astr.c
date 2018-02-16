/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_astr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:23:36 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/16 20:29:54 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					astr_to_buf(char **argv, t_qbuf *buf, int last)
{
	int					i;

	i = 0;
	while (argv[i] != NULL)
	{
		qbuf_add(buf, argv[i]);
		if (argv[i + 1] != NULL)
			qbuf_addc(buf, ' ');
		else
			qbuf_add(buf, last ? "" : " | ");
		i++;
	}
}

void					astr_env_replace(char ***env, char *key, char *new_v)
{
	int					i;

	if ((i = ft_astr_getkey(*env, key, ft_strlen(key))) == -1)
		ft_astr_append(env, ft_strdup(new_v));
	else
	{
		dprintf(STDERR_FILENO, "%s not in environ\n", key);
		ft_strdel((*env) + 1);
		(*env)[i] = ft_strdup(new_v);
	}
}
