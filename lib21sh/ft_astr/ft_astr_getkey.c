/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_getkey.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:40:54 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/07 15:28:39 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

int					ft_astr_getkey(char **env, char *key, int pos)
{
	int				i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, pos) == 0)
		{
			if (env[i][pos] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

char				*ft_astr_getval(char **env, char *key)
{
	int				pos;
	int				ind;

	pos = ft_strlen(key);
	if ((ind = ft_astr_getkey(env, key, pos)) == -1)
		return (NULL);
	return (env[ind] + pos + 1);
}
