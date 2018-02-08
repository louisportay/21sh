/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_kvp_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:08:44 by lportay           #+#    #+#             */
/*   Updated: 2018/01/27 16:09:15 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_kvp	*copy_kvp_env(char **env)
{
	t_kvp	*kvp_env;
	char	**tmp;
	size_t	len;

	if (!(tmp = env))
		return (NULL);
	len = 0;
	while (*tmp++)
		len++;
	if (!(kvp_env = (t_kvp *)malloc(sizeof(t_kvp) * (len + 1))))
		return (NULL);
	kvp_env[len].key = NULL;
	kvp_env[len].val = NULL;
	while (len--)
	{
		if (!(*tmp = ft_strdup(env[len])))
				return (NULL);

		kvp_env[len].key = *tmp;
		kvp_env[len].val = ft_strdup(ft_strchr(*tmp, '=') + 1);
		*ft_strchr(*tmp, '=') = '\0'; 
	}
	return (kvp_env);
}
