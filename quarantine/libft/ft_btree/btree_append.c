/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 18:23:33 by lportay           #+#    #+#             */
/*   Updated: 2018/01/25 18:23:51 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		btree_append(t_btree *root, t_btree *elem)
{
	if (!root->left)
	{
		root->left = elem;
		root->left->parent = root->left;
		root = root->left;
		return (LEFT);
	}
	else if (!root->right)
	{
		root->right = elem;
		root->right->parent = root->left;
		root = root->right;
		return (RIGHT);
	}
	return (-1);
}
