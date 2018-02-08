/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:00:28 by lportay           #+#    #+#             */
/*   Updated: 2017/11/06 17:21:30 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the maillon that give 0 as a result when compared with data_ref
** (with 'cmpf'). Returns NULL otherwise
*/

void *btree_search_item(t_btree *root, void *data_ref, int
(*cmpf)(void *, void *))
{
	void *ret;

	if (!root)
		return (NULL);
	if (root->left && (ret = btree_search_item(root->left, data_ref, cmpf)))
		return (ret);
	if ((*cmpf)(root->data, data_ref) == 0)
		return (root);
	if (root->right && (ret = btree_search_item(root->right, data_ref, cmpf)))
		return (ret);
	return (NULL);
}
