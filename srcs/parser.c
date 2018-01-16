/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 16:57:59 by lportay           #+#    #+#             */
/*   Updated: 2018/01/16 18:04:35 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"


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

void	*parse_error(t_btree **ast)
{
	btree_delete(ast, NULL);
	return (NULL);
}

t_btree	*parser(t_token *tok)
{
	t_btree *ast;	//the whole tree that we complete 
	t_btree *head;	//save for later

	ast = btree_create_node((void *)tok);
	head = ast;
	tok = tok->next;

	if (tok->type == OR_IF || tok->type == AND_IF || tok->type == SEMICOL || tok->type == OR)
		return (parse_error(&head));


	while (tok->type != NEWLINE)
	{
		if (tok->type == ASSIGNMENT_WORD || tok->type == WORD)
		{
			if (btree_append(ast, btree_create_node((void *)tok)) == LEFT)
				ast = ast->left;
			else
				ast = ast->right;
		}

		else if (tok->type == IO_NUMBER)
		{
			if (btree_append(ast, btree_create_node((void *)tok->next)) == LEFT)
				ast = ast->left;
			else
				ast = ast->right;
			btree_append(ast, btree_create_node((void *)tok));
			tok = tok->next;
		}

		else if (tok->type == LESS || tok->type == GREAT || tok->type == DLESS || tok->type == DGREAT || tok->type == LESSAND || tok->type == GREATAND)
		{
			if (tok->next->type != WORD)
				return (parse_error(&head));

			if (btree_append(ast, btree_create_node((void *)tok)) == LEFT)
				ast = ast->left;
			else
				ast = ast->right;
			ast->right = btree_create_node((void *)tok->next);
			ast = ast->right;
			tok = tok->next;
		}

		else if (tok->type == OR_IF || tok->type == AND_IF || tok->type == SEMICOL || tok->type == OR)
		{
			if (tok->next->type == OR || tok->next->type == OR_IF || tok->next->type == AND_IF || tok->next->type == SEMICOL || tok->next->type == NEWLINE)
				return (parse_error(&head));
			else
			{
				btree_insert(head, head->left, btree_create_node((void *)tok));
				ast = head->left;
			}
		}

		tok = tok->next;
	}
	return (head);
}
