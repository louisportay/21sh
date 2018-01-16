/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_btree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:56:05 by lportay           #+#    #+#             */
/*   Updated: 2018/01/15 17:40:12 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Print in colors the tree (red for left, blue for right)
*/

void	print_btree(t_btree *tree, bool status, unsigned lvl, void (*print_func)(void *))
{
	if (tree->parent)
		write(STDOUT_FILENO, "|", 1);
	if (lvl)
		ft_putnchar(' ', (lvl - 1) * 3);
	if (tree->parent)
		write(STDOUT_FILENO, "-- ", 3);
	if (status == LEFT && lvl)
		ft_putstr(RED);
	else if (status == RIGHT && lvl)
		ft_putstr(BLUE);
	(*print_func)(tree->data);
	ft_putstr(RESET"\n");
	if (tree->left)
		print_btree(tree->left, LEFT, lvl + 1, print_func);
	if (tree->right)
		print_btree(tree->right, RIGHT, lvl + 1, print_func);
}
