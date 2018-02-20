/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:22:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/12/14 20:15:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void                     lrm(t_ctx *ctx, char *str)
{
    int                         i;
    int                         j;
    char                        *s;

    i = ft_strlen(str);
    if ((j = ft_astr_getkey(ctx->environ, str, i)) != -1)
    {
        s = ft_astr_remove_at(&ctx->environ, j);
        ft_strdel(&s);
    }
}

static int                      ladd_err(t_proc *p, int i, char *name,
                                            t_list **curr)
{
    t_list                      *n;
    char                        *str;
    
    asprintf(&str, "221sh: %s: %s: not a valid identifier\n",
                name, p->argv[i]);
    n = list_create(str);
    ft_list_insert(&p->data.out, curr, n);
    return (1);
}

int                             ft_rmenv(t_proc *p, t_ctx *ctx, char *name)
{
    int                         i;
    int                         ret;
    t_list                      *curr;

    p->type = BUILTIN;
    i = 1;
    ret = 0;
    while (p->argv[i] != NULL)
    {
        if (is_identifier(p->argv[i]))
            lrm(ctx, p->argv[i]);
        else
            ret |= ladd_err(p, i, name, &curr);
        i++;
    }
    return (ret);
}

int                             ft_unsetenv(t_proc *p, t_ctx *ctx)
{
    return (ft_rmenv(p, ctx, "unsetenv"));
}

int                             ft_unset(t_proc *p, t_ctx *ctx)
{
    return (ft_rmenv(p, ctx, "unset"));
}
