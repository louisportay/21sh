/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:48:36 by lportay           #+#    #+#             */
/*   Updated: 2018/03/23 11:47:01 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_sane(char *str, int *end)
{
	int				i;

	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	*end = i;
	return (1);
}

int	is_identifier(char *str)
{
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (0);
	while (*str != '\0')
	{
		if (ft_isalnum(*str) == 0 && *str != '_')
			return (0);
		str++;
	}
	return (1);
}
