/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:36:47 by lportay           #+#    #+#             */
/*   Updated: 2018/01/25 18:25:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

#define LEFT 0
#define RIGHT 1

typedef struct			s_btree
{
	struct s_btree		*parent;
	struct s_btree		*left;
	struct s_btree		*right;
	void				*data;
}						t_btree;

enum				e_rb_color
{
	RB_BLACK,
	RB_RED
};

typedef struct			s_rb_node
{
	struct s_rb_node	*parent;
	struct s_rb_node	*left;
	struct s_rb_node	*right;
	void			*data;
	enum e_rb_color		color;
}				t_rb_node;

t_btree	*btree_create_node(void *data);
void   	btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void   	btree_apply_suffix(t_btree *root, void (*applyf)(void *));
void   	btree_apply_infix(t_btree *root, void (*applyf)(void *));
void   	btree_insert_data(t_btree **root, void *item, int (*cmpf)(void *, void *));
void   	*btree_search_item(t_btree *root, void *data_ref, int (*cmpf)(void *, void *));
void   	print_btree(t_btree *tree, bool status, unsigned lvl, void (*print_func)(void *));
void   	btree_delete(t_btree **tree, void (*del)(void *));
int	   	btree_append(t_btree *root, t_btree *elem);
void   	btree_insert(t_btree *root, t_btree *leaf, t_btree *elem);

#endif
