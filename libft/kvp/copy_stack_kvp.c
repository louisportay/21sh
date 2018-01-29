/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_stack_kvp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:06:15 by lportay           #+#    #+#             */
/*   Updated: 2018/01/27 16:08:18 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_kvp	*copy_stack_kvp(t_kvp *stack_kvp, size_t len)
{
	t_kvp	*heap_kvp;
	t_kvp	*tmp;

	if(!stack_kvp || !len)
		return (NULL);
	if (!(heap_kvp = (t_kvp *)malloc(sizeof(t_kvp) * (len + 1))))
		return (NULL);
	tmp = heap_kvp;
	while (stack_kvp->key)
	{
		tmp->key = ft_strdup(stack_kvp->key);	
		tmp->val = ft_strdup(stack_kvp->val);	
		stack_kvp++;
		tmp++;
	}
	tmp->key = NULL;
	tmp->val = NULL;
	return (heap_kvp);	
}
