/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_jobspec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 15:37:51 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/15 10:27:22 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void			*lamb(char *builtin, char *str)
{
	dprintf(STDERR_FILENO, "21sh: %s: %s: %s\n", builtin, str, BU_JOB_AMB);
	return (NULL);
}

static t_job		*lneedle(t_ctx *ctx, char *needle)
{
	size_t			i;
	size_t			k;
	t_job			*j;
	t_proc			*p;

	i = 0;
	j = NULL;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
		{
			p  = ctx->bg_jobs[i]->procs;
			while (p != NULL)
			{
				k = 0;
				while (p->argv[k] != NULL)
				{
					if (ft_strstr(p->argv[k], needle) != NULL)
					{
						if (j == NULL)
							j = ctx->bg_jobs[i];
						else
							return (lamb("bg", needle));
					}
					k++;
				}
				p = p->next;
			}
		}
		i++;
	}
	return (j);
}

static t_job		*lstrcmp(t_ctx *ctx, char *str)
{
	size_t			len;
	size_t			i;
	t_job			*j;
	t_proc			*p;

	i = 0;
	j = NULL;
	len = ft_strlen(str);
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
		{
			p = ctx->bg_jobs[i]->procs;
			while (p != NULL)
			{
				if (ft_strncmp(p->argv[0], str, len) == 0)
				{
					if (j == NULL && p == ctx->bg_jobs[i]->procs)
						j = ctx->bg_jobs[i];
					else
						return (lamb("bg", str));
				}
				p = p->next;
			}
		}
		i++;
	}
	return (j);
}

t_job				*jc_jobspec(t_proc *p, char *caller, char *argv,
								t_ctx *ctx)
{
	t_job			*j;
	size_t			i;
	int				n;
	t_list			*l;
	char			*str;

	j = NULL;
	i = 0;
	if (argv[i] == '%')
		i++;
	if (argv[i] == '\0'
		|| (argv[i] == '+' && argv[i + 1] == '\0')
		|| (argv[i] == '%' && argv[i + 1] == '\0'))
		j = (ctx->bgs != NULL) ? (t_job *)ctx->bgs->content : NULL;
	else if (argv[i] == '-' && argv[i + 1] == '\0')
	{
		if (ctx->bgs == NULL)
			j = NULL;
		else if (ctx->bgs->next == NULL)
			j = (t_job *)ctx->bgs->content;
		else
			j = (t_job *)ctx->bgs->next->content;
	}
	else if (ft_isnumber(argv + i))
	{
		n = ft_atoi(argv + i) - 1;
		if (n < 0 || (size_t)n > ctx->bg_cnt || ctx->bg_jobs[n] == NULL)
		{
			asprintf(&str, "221sh: %s: %s: %s\n", caller, argv, BU_JOB_NO);
			l = list_create(str);
			ft_assert((void **[]){(void **)&str, (void **)&l}, 2);
			if (p->data.out == NULL)
				p->data.out = l;
			else
				ft_list_last(p->data.out)->next = l;
		}
		else
			j = ctx->bg_jobs[n];
	}
	else if (argv[i] == '?')
		j = lneedle(ctx, argv + i + 1);
	else
		j = lstrcmp(ctx, argv + i);
	return (j);
}
