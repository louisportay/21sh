/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_getkey.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:40:54 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 15:37:56 by vbastion         ###   ########.fr       */
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
