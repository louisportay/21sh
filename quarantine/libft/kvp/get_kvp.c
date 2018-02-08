/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_kvp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:28:16 by lportay           #+#    #+#             */
/*   Updated: 2018/01/27 16:28:33 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_kvp(const char *name, t_kvp *kvp)
{
	while (kvp->key && ft_strcmp(name, kvp->key))
		kvp++;
	if (kvp)
		return (kvp->val);
	else
		return (NULL);
}
