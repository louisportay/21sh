/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 19:06:13 by lportay           #+#    #+#             */
/*   Updated: 2017/11/06 17:20:17 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*btree_create_node(void *data)
{
	t_btree *node;

	if ((node = (t_btree *)malloc(sizeof(t_btree))) == NULL)
		return (NULL);
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->data = data;
	return (node);
}
