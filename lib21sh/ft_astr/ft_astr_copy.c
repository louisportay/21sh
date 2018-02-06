/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:01:14 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 15:37:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

int			ft_astr_ncopy(char **dst, char **src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (0);
}

int			ft_astr_copy(char **dst, char **src)
{
	size_t	i;

	i = 0;
	while (src[i] != NULL)
	{
		dst[i] = src[i];
		i++;
	}
	return (0);
}

int			ft_astr_ndeepcopy(char **dst, char **src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((dst[i] = ft_strdup(src[i])) == NULL)
		{
			ft_astr_nfree(dst, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

int			ft_astr_deepcopy(char **dst, char **src)
{
	size_t	i;

	i = 0;
	while (src[i] != NULL)
	{
		if ((dst[i] = ft_strdup(src[i])) == NULL)
		{
			ft_astr_nfree(dst, i);
			return (-1);
		}
		i++;
	}
	return (0);
}
