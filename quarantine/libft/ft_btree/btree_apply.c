/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:57:47 by lportay           #+#    #+#             */
/*   Updated: 2018/01/17 10:19:45 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** These functions will map the given tree (every reachable node from the root)
*/

/*
** PreOrder
*/

void btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	(*applyf)(root->data);
	if (root->left)
		btree_apply_prefix(root->left, applyf);
	if (root->right)
		btree_apply_prefix(root->right, applyf);
}

/*
** PostOrder
*/

void btree_apply_suffix(t_btree *root, void (*applyf)(void *))
{
	if (root->left)
		btree_apply_prefix(root->left, applyf);
	if (root->right)
		btree_apply_prefix(root->right, applyf);
	(*applyf)(root->data);
}

/*
** InOrder
*/

void btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root->left)
		btree_apply_prefix(root->left, applyf);
	(*applyf)(root->data);
	if (root->right)
		btree_apply_prefix(root->right, applyf);
}
