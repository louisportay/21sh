/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_dollarexec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:01:02 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/10 15:59:39 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static void			vtok_plus(t_lvar *lvar, char *lhs, char *rhs)
{
	char			*elhs;

	elhs = ft_env_get_value(lvar->env->env, lhs);
	if (elhs == NULL
		&& (elhs = ft_env_get_value(lvar->env->locals, lhs)) == NULL)
		return ;
	ft_mb_add(&lvar->buf, rhs, ft_strlen(rhs));
}

static void			vtok_minus(t_lvar *lvar, char *lhs, char *rhs)
{
	char			*elhs;

	elhs = ft_env_get_value(lvar->env->env, lhs);
	if (elhs == NULL
		&& (elhs = ft_env_get_value(lvar->env->locals, lhs)) == NULL)
		ft_mb_add(&lvar->buf, rhs, ft_strlen(rhs));
	else
		ft_mb_add(&lvar->buf, elhs, ft_strlen(elhs));
}

void				vtok_dollexec(t_lvar *lvar, char *str[2], char c)
{
	if (c == '+')
		vtok_plus(lvar, str[0], str[1]);
	else if (c == '-')
		vtok_minus(lvar, str[0], str[1]);
	else
		vtok_plus(lvar, str[0], str[1]);
}
