/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:59:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/20 18:34:08 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_export(t_proc *p, t_ctx *ctx)
{
	return (modenv(p, ctx, "export"));
}

int	ft_setenv(t_proc *p, t_ctx *ctx)
{
	return (modenv(p, ctx, "setenv"));
}
