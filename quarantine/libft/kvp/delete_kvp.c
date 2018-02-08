/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_kvp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:10:17 by lportay           #+#    #+#             */
/*   Updated: 2018/01/27 16:10:32 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	delete_kvp(t_kvp **addr_kvp_env)
{
	t_kvp *tmp;

	tmp = *addr_kvp_env;
	while (tmp->key)
	{
		free(tmp->key);
		free(tmp->val);
		tmp++;
	}
	free(*addr_kvp_env);
	*addr_kvp_env = NULL;
}
