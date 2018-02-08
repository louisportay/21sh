/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 18:22:22 by lportay           #+#    #+#             */
/*   Updated: 2018/01/25 18:23:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** the inserted node should not have any children nodes
** if any, they will be possibly lost.
*/

void	btree_insert(t_btree *root, t_btree *leaf, t_btree *elem)
{
	if (root->left == leaf)
	{
		elem->left = leaf;
		root->left = elem;
	}
	else if (root->right == leaf)
	{
		elem->right = leaf;
		root->right = elem;
	}
	leaf->parent = elem;
	elem->parent = root;
}
