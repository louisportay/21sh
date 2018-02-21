/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:12:44 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 15:37:56 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

char				*ft_env_find(char **env, char *key)
{
	size_t			len;

	if (env == NULL || key == NULL)
		return (NULL);
	len = ft_strlen(key);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, key, len) == 0 && (*env)[len] == '=')
			return ((*env) + len + 1);
		env++;
	}
	return (NULL);
}
