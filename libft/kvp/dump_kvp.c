/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_kvp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:09:34 by lportay           #+#    #+#             */
/*   Updated: 2018/01/27 16:09:49 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dump_kvp(t_kvp *kvp)
{
	while (kvp->key)
	{
		ft_putstr(kvp->key);
		ft_putchar('=');
		if (kvp->val)
			ft_putstr(kvp->val);
		ft_putchar('\n');
		kvp++;
	}
}
