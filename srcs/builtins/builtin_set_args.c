/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 17:37:09 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/24 15:25:09 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define BU_S_USG ("21sh: usage: set [-+][Fabdfhnolx]")

#define BU_S_HPR ("l: displays local variables. With '+l' shows env beforehand")
#define BU_S_HSE ("o: displays options. '+o' prints it as commands to set them")
#define BU_S_HEX ("a: assignment commands are exported")
#define BU_S_HBG ("b: set job notifications to be immediate")
#define BU_S_HON ("x: prints each action done before execution")
#define BU_S_HFN ("f: inhib globbing expansion")
#define BU_S_HDO ("d: adds hidden files to globbing")
#define BU_S_HNU ("n: if expansion fails, replace it with a null string")
#define BU_S_HFA ("F: if expansion fails, abords pipe execution")
#define BU_S_HEL ("h: displays this help. '+h' adds usage beforehand")

static int			set_help(t_proc *p, int usage)
{
	char			*str;

	asprintf(&str, "1%s%c%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
				usage ? BU_S_USG : "", usage ? '\n' : '\r',
				BU_S_HPR, BU_S_HSE, BU_S_HEX, BU_S_HBG, BU_S_HON, BU_S_HFN,
				BU_S_HDO, BU_S_HNU, BU_S_HFA, BU_S_HEL);
	p->type = BU_STR;
	p->data.str = str;
	return (-1);
}

static int			lusage(t_proc *p, char c, char ec)
{
	char			*str;

	if (ec)
		asprintf(&str, "221sh: set: -%c: invalid argument\n%s\n", c, BU_S_USG);
	else
		asprintf(&str, "2%s\n", BU_S_USG);
	p->type = BU_STR;
	p->data.str = str;
	return (-1);
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
		else if (p->argv[i][j] == 'a')
			*tmp |= BU_SET_EXPOR;
		else if (p->argv[i][j] == 'b')
			*tmp |= BU_SET_BGCMD;
		else if (p->argv[i][j] == 'f')
			*tmp |= BU_SET_FNEXP;
		else if (p->argv[i][j] == 'x')
			*tmp |= BU_SET_ONCMD;
		else if (p->argv[i][j] == 'd')
			*tmp |= DOTGLOB;
		else if (p->argv[i][j] == 'n')
			*tmp |= NULLGLOB;
		else if (p->argv[i][j] == 'F')
			*tmp |= FAILGLOB;
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
		else if (p->argv[i][j] == 'a')
			*tmp &= ~BU_SET_EXPOR;
		else if (p->argv[i][j] == 'b')
			*tmp &= ~BU_SET_BGCMD;
		else if (p->argv[i][j] == 'f')
			*tmp &= ~BU_SET_FNEXP;
		else if (p->argv[i][j] == 'x')
			*tmp &= ~BU_SET_ONCMD;
		else if (p->argv[i][j] == 'd')
			*tmp &= ~DOTGLOB;
		else if (p->argv[i][j] == 'n')
			*tmp &= ~NULLGLOB;
		else if (p->argv[i][j] == 'F')
			*tmp &= ~FAILGLOB;
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
		if (p->argv[i][0] == '-')
		{
			if ((opts[1] = lget_min(p, i, &tmp)) == -1)
				return (-1);
			opts[0] |= opts[1];
		}
		else if (p->argv[i][0] == '+')
		{
			if ((opts[1] = lget_max(p, i, &tmp)) == -1)
				return (-1);
			opts[0] |= opts[1];
		}
		else
			break ;
		i++;
	}
	ctx->set = tmp;
	return (opts[0]);
}
