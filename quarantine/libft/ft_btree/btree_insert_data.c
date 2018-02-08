/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:59:21 by lportay           #+#    #+#             */
/*   Updated: 2017/11/06 17:21:09 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void insert_node(t_btree **branch, t_btree **leaf, void *item)
{
	*leaf = btree_create_node(item);
	(*leaf)->parent = *branch;
	*branch = NULL;
}

void 	btree_insert_data(t_btree **root, void *item, int
(*cmpf)(void *, void *))
{
	t_btree *tmp;

	if (!(*root))
		*root = btree_create_node(item);
	else
	{
		tmp = *root;
		while (tmp)
		{
			
			if (tmp->left && (*cmpf)(tmp->data, item) > 0)
				tmp = tmp->left;
			else if (tmp->right && (*cmpf)(tmp->data, item) <= 0)
				tmp = tmp->right;
			else if (!tmp->left && (*cmpf)(tmp->data, item) > 0)
				insert_node(&tmp, &tmp->left, item);
			else if (!tmp->right && (*cmpf)(tmp->data, item) <= 0)
				insert_node(&tmp, &tmp->right, item);
		}
	}
}
