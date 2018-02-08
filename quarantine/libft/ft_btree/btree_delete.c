/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 18:17:28 by lportay           #+#    #+#             */
/*   Updated: 2018/01/04 18:40:10 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	delete_each_node_content(t_btree **tree, void (*del)(void *))
{
	if ((*tree)->left)
		delete_each_node_content(&(*tree)->left, del);
	if ((*tree)->right)
		delete_each_node_content(&(*tree)->right, del);
	(*del)((*tree)->data);
	free(*tree);
}

static void	delete_each_node(t_btree **tree)
{
	if ((*tree)->left)
		delete_each_node(&(*tree)->left);
	if ((*tree)->right)
		delete_each_node(&(*tree)->right);
	free(*tree);
}
	
void	btree_delete(t_btree **tree, void (*del)(void *))
{
	if (del)
		delete_each_node_content(tree, del);
	else
		delete_each_node(tree);
	*tree = NULL;
}
