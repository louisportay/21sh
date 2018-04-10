/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set_args2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 20:19:39 by lportay           #+#    #+#             */
/*   Updated: 2018/04/10 09:33:29 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int			lusage(t_proc *p, char c, char ec)
{
	if (ec)
	{
		ft_dprintf(STDERR_FILENO, "21sh: set: -%c: invalind argument\n%s\n",
					c, BU_S_USG);
	}
	else
		ft_dprintf(STDERR_FILENO, "%s\n", BU_S_USG);
	p->type = BUILTIN;
	return (-1);
}

static inline int	laddarg(u_short *tmp, char c)
{
	if (c == 'a')
		*tmp |= BU_SET_EXPOR;
	else if (c == 'B')
		*tmp |= BRACE_EXPAND;
	else if (c == 'f')
		*tmp |= BU_SET_FNEXP;
	else if (c == 'x')
		*tmp |= BU_SET_ONCMD;
	else if (c == 'd')
		*tmp |= DOTGLOB;
	else if (c == 'n')
		*tmp |= NULLGLOB;
	else if (c == 'F')
		*tmp |= FAILGLOB;
	else
		return (0);
	return (1);
}

static inline int	lrmarg(u_short *tmp, char c)
{
	if (c == 'a')
		*tmp &= ~BU_SET_EXPOR;
	else if (c == 'B')
		*tmp &= ~BRACE_EXPAND;
	else if (c == 'f')
		*tmp &= ~BU_SET_FNEXP;
	else if (c == 'x')
		*tmp &= ~BU_SET_ONCMD;
	else if (c == 'd')
		*tmp &= ~DOTGLOB;
	else if (c == 'n')
		*tmp &= ~NULLGLOB;
	else if (c == 'F')
		*tmp &= ~FAILGLOB;
	else
		return (0);
	return (1);
}

int					get_min(t_proc *p, int i, u_short *tmp)
{
	int				j;
	int				ret;

	ret = 0;
	j = 1;
	while (p->argv[i][j] != '\0')
	{
		if (p->argv[i][j] == 'l')
			ret |= BU_SET_PRLOC;
		else if (p->argv[i][j] == 'o')
			ret |= BU_SET_PRSET;
		else if (laddarg(tmp, p->argv[i][j]))
			;
		else if (p->argv[i][j] == 'h')
			return (set_help(p, 0));
		else
			return (lusage(p, p->argv[i][j], 1));
		j++;
	}
	return (ret);
}

int					get_max(t_proc *p, int i, u_short *tmp)
{
	int				j;
	int				ret;

	ret = 0;
	j = 1;
	while (p->argv[i][j] != '\0')
	{
		if (p->argv[i][j] == 'l')
			ret |= BU_SET_PRVAR;
		else if (p->argv[i][j] == 'o')
			ret |= BU_SET_PRCMD;
		else if (lrmarg(tmp, p->argv[i][j]))
			;
		else if (p->argv[i][j] == 'h')
			return (set_help(p, 1));
		else
			return (lusage(p, p->argv[i][j], 1));
		j++;
	}
	return (ret);
}