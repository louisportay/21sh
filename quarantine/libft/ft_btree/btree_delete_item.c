/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_delete_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:17:01 by lportay           #+#    #+#             */
/*   Updated: 2017/11/06 18:38:18 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void btree_delete_item(t_btree **root, void *data, int (*cmpf)(void *, void *), void (*freef)(void *))
{
	t_btree *tmp;
	
	if (!(tmp = btree_search_item(*root, data, cmpf)))
		return ;
	if (!tmp->left && !tmp->right)
	{
		(*freef)(tmp->data);
		if (tmp->parent->left == tmp)
			tmp->parent->left = NULL;
		else
			tmp->parent->right = NULL;
		free(tmp);
	}
	//TO CONTINUE
}

int main(void)
{
	t_btree *tree;	

	btree_insert_data(&tree, "A", strcmp); //caster strcmp
}
