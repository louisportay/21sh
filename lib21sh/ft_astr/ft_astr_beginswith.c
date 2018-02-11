/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_beginswith.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:01:03 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/11 14:51:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

int				ft_astr_beginswith(char **astr, char *value)
{
	int			i;
	size_t		len;

	if (astr == NULL || *astr == NULL || value == NULL)
		return (-1);
	i = 0;
	len = ft_strlen(value);
	while (astr[i] != NULL)
	{
		if ((ft_strlen(astr[i])) >= len && ft_strncmp(astr[i], value, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int				ft_astr_nbeginswith(char **astr, char *value, size_t pos)
{
	int			i;

	if (astr == NULL || *astr == NULL || value == NULL)
		return (-1);
	i = 0;
	while (astr[i] != NULL)
	{
		if (ft_strncmp(astr[i], value, pos) == 0)
			return (i);
		i++;
	}
	return (-1);
}
