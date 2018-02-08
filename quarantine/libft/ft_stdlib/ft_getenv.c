/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 17:58:57 by lportay           #+#    #+#             */
/*   Updated: 2017/08/23 17:57:42 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Renvoie la valeur de la clé 'name' si elle est trouvé dans le tableau 'env'
** sinon renvoie NULL
*/

char	*ft_getenv(const char *name, char **env)
{
	char	*tmp;
	int		len;

	if (!name)
		return (NULL);
	tmp = ft_strjoin(name, "=");
	len = ft_strlen(tmp);
	while (*env)
	{
		if (ft_strncmp(*env, tmp, len) == 0)
		{
			ft_strdel(&tmp);
			return (*env + len);
		}
		env++;
	}
	ft_strdel(&tmp);
	return (NULL);
}
