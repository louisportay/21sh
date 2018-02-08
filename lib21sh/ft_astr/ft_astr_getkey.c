/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_getkey.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:40:54 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/07 15:32:38 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

int					ft_astr_getkey(char **env, char *key, int eq_pos)
{
	int				i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, eq_pos) == 0)
		{
			if (env[i][eq_pos] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

char				*ft_astr_getval(char **env, char *key)
{
	int				eq_pos;
	int				pos;

	eq_pos = ft_strlen(key);
	if ((pos = ft_astr_getkey(env, key, eq_pos)) == -1)
		return (NULL);
	return (env[pos] + eq_pos + 1);
}
