/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_rmdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:22:39 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/19 13:47:56 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

#include <stdio.h>

static int	lastr_clean(char ***astr, size_t len, size_t cnt)
{
	char	**ret;
	size_t	i;
	size_t	j;

	if ((ret = (char **)ft_memalloc(sizeof(char *) * (cnt + 1))) == NULL)
	{
		ft_astr_clear(astr);
		return (-1);
	}
	i = 0;
	j = 0;
	while (i < len)
	{
		if ((*astr)[i] != NULL)
		{
			ret[j] =
				(*astr)[i];
			j++;
		}
		i++;
	}
	ft_memdel((void **)astr);
	*astr = ret;
	return (1);
}

static void	init_var(size_t *i, size_t *cnt, char ***arr, char **astr)
{
	*i = 0;
	*cnt = 0;
	*arr = astr;
}

int			astr_rmdup(char ***astr)
{
	size_t	i;
	size_t	j;
	size_t	cnt;
	int		is_dup;
	char	**arr;

	init_var(&i, &cnt, &arr, *astr);
	while (arr[i] != NULL)
	{
		j = 0;
		is_dup = 0;
		while (j < i)
		{
			if (arr[j] != NULL && ft_strcmp(arr[i], arr[j]) == 0)
			{
				is_dup = 1;
				ft_strdel(arr + i);
				break ;
			}
			j++;
		}
		cnt += is_dup == 0;
		i++;
	}
	return (lastr_clean(astr, i, cnt) == -1);
}
