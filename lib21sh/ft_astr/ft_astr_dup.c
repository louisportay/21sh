/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:01:26 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 15:37:56 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

char			**ft_astr_dup(char **astr)
{
	char		**ret;
	size_t		len;
	size_t		i;

	len = ft_astr_len(astr);
	if ((ret = (char **)ft_memalloc(sizeof(void *) * (len + 1))) == NULL)
		return (NULL);
	i = 0;
	while (astr[i] != NULL)
	{
		ret[i] = ft_strdup(astr[i]);
		i++;
	}
	return (ret);
}
