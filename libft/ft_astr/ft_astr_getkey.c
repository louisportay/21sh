/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_getkey.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:40:54 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/26 15:38:18 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

int					ft_astr_getkey(char **env, char *const key, int eq_pos)
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

int					ft_astr_getlowkey(char **arr, char *key)
{
	size_t			i;
	size_t			j;
	int				eq;

	i = (size_t)ft_strindex(key, '=');
	if ((eq = (i != (size_t)-1)) == 0)
		i = ft_strlen(key);
	j = 0;
	while (arr[j] != NULL)
	{
		if (ft_strncmp(arr[j], key, i) == 0
			&& (arr[j][i] == '\0' || arr[j][i] == '='))
			return ((int)j);
		j++;
	}
	return (-1);
}
