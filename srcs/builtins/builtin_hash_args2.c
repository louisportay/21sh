/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_args2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 20:03:25 by lportay           #+#    #+#             */
/*   Updated: 2018/04/09 20:04:14 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int				l_isdir(char *path)
{
	struct stat			stats;

	if (stat(path, &stats) != -1)
	{
		if (S_ISDIR(stats.st_mode))
		{
			ft_dprintf(STDERR_FILENO, "21sh: hash: %s is a directory\n", path);
			return (1);
		}
	}
	return (0);
}

static int				ladderr(void)
{
	ft_dprintf(STDERR_FILENO, BU_H_EPREQU);
	return (-1);
}

static char				*lnewval(char *str, int *k, int newk)
{
	if (l_isdir(str))
		return (NULL);
	*k = newk;
	return (ft_strdup(str));
}

int				hash_inh(t_proc *p, t_ctx *ctx, int i, int j)
{
	char				*key;
	char				*value;
	int					k;

	if (p->argv[i][j + 1] != '\0')
	{
		if (p->argv[i + 1] == NULL)
			return (ladderr());
		if ((value = lnewval(p->argv[i] + j + 1, &k, i + 1)) == NULL)
			return (-1);
	}
	else
	{
		if (p->argv[i + 1] == NULL || p->argv[i + 2] == NULL)
			return (ladderr());
		if ((value = lnewval(p->argv[i + 1], &k, i + 2)) == NULL)
			return (-1);
	}
	while (p->argv[k + 1] != NULL)
		k++;
	key = ft_strdup(p->argv[k]);
	hash_add_or_mod(ctx->hash, key, value, &ft_memdel);
	return (0);
}
