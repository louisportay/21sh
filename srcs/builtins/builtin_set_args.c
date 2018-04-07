/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 17:37:09 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 14:07:36 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int			set_help(t_proc *p, int usage)
{
	p->type = BUILTIN;
	ft_dprintf(STDERR_FILENO, "%s%c%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
				usage ? BU_S_USG : "", usage ? '\n' : '\r',
				BU_S_HPR, BU_S_HSE, BU_S_HEX, BU_S_HBG, BU_S_HON, BU_S_HFN,
				BU_S_HDO, BU_S_HNU, BU_S_HFA, BU_S_HEL);
	return (-1);
}

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
	else if (c == 'b')
		*tmp |= BU_SET_BGCMD;
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
	else if (c == 'b')
		*tmp &= ~BU_SET_BGCMD;
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

static int			lget_min(t_proc *p, int i, u_short *tmp)
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

static int			lget_max(t_proc *p, int i, u_short *tmp)
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

int					bu_set_getopts(t_proc *p, t_ctx *ctx, int i)
{
	int				opts[2];
	u_short			tmp;

	opts[0] = 0;
	tmp = ctx->set;
	while (p->argv[i] != NULL)
	{
		if (p->argv[i][0] == '-' && ft_isalpha(p->argv[i][1]))
		{
			if ((opts[1] = lget_min(p, i, &tmp)) == -1)
				return (-1);
			opts[0] |= opts[1];
		}
		else if (p->argv[i][0] == '+' && ft_isalpha(p->argv[i][1]))
		{
			if ((opts[1] = lget_max(p, i, &tmp)) == -1)
				return (-1);
			opts[0] |= opts[1];
		}
		else if (p->argv[i][0] == '-' || p->argv[i][0] == '+')
		{
			ft_dprintf(STDERR_FILENO, "21sh: set: %s: Invalid argument\n%s\n",
						p->argv[i], BU_S_USG);
			return (-1);
		}
		else
			break ;
		i++;
	}
	ctx->set = tmp;
	return (opts[0]);
}
