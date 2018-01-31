/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_addvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 11:52:54 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/09 17:30:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

void				vtok_addvar(t_membuf *buf, t_environ *env, char *key)
{
	char			*value;

	value = ft_env_get_value(env->env, key);
	if (value == NULL && (value = ft_env_get_value(env->locals, key)) == NULL)
		return ;
	ft_mb_add(buf, value, ft_strlen(value));
}
