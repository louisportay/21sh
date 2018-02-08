/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_kvp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:26:06 by lportay           #+#    #+#             */
/*   Updated: 2018/01/27 16:37:39 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		set_kvp(char *name, const char *value, t_kvp **addr_kvp)
{
	t_kvp	*tmp;
	t_kvp	*new_env;
	size_t	len;

	if (!name || !ft_strlen(name) || !(*addr_kvp))
		return (-1);
	len = 0;
	tmp = *addr_kvp;
	while (tmp->key && ft_strcmp(name, tmp->key))
	{
		tmp++;
		len++;
	}
	if (tmp->key)
	{
		free(name);
		free(tmp->val);
		tmp->val = (char *)value;
	}
	else
	{
		if (!(new_env = (t_kvp *)malloc(sizeof(t_kvp) * (len + 2))))
			return (-1);
		tmp = new_env;
		while ((*addr_kvp)->key)
		{
			tmp->key = (*addr_kvp)->key;
			tmp->val = (*addr_kvp)->val;
			tmp++;
			(*addr_kvp)++;
		}
		tmp->key = name;
		tmp->val = (char *)value;
		tmp++;
		tmp->key = NULL;
		tmp->val = NULL;
		free(*addr_kvp - len);
		*addr_kvp = new_env;
	}
	return (0);
}
