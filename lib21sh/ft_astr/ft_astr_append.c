/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:00:57 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 15:37:56 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

int			ft_astr_append(char ***astr, char *value)
{
	size_t	len;
	char	**ret;

	if (value == NULL)
		return (1);
	len = ft_astr_len(*astr);
	if ((ret = (char **)ft_memalloc(sizeof(char *) * (len + 2))) == NULL)
		return (0);
	if (*astr == NULL)
		*ret = value;
	else
	{
		ft_astr_copy(ret, *astr);
		ret[len] = value;
		free(*astr);
	}
	*astr = ret;
	return (1);
}
