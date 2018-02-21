/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 12:01:01 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/07 12:38:25 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include <sys/types.h>
# include <stdlib.h>

typedef struct s_list		t_list;

struct						s_list
{
	void					*content;
	t_list					*next;
};

typedef int					(*t_cmp)();

/*
**	FUNCTIONS
*/

/*
**	SRC/FT_LIST_ADD.C
*/

void						list_add(t_list **head, t_list *elem);
t_list						*list_addcontent(t_list **head, void *content);
t_list						*list_insert(t_list **head, void *content,
											int (*cmp)());

/*
**	SRC/FT_LIST_PUSH.C
*/

t_list						*list_push_front(t_list **head, void *content);
t_list						*list_push(t_list **head, t_list *elem);

/*
**	SRC/FT_LIST_COUNT.C
*/

size_t						ft_list_len(t_list *list);
size_t						ft_list_count(t_list *list, int (*assert)(void *));

/*
**	SRC/FT_LIST_PREPEND
*/

void						list_prepend(t_list **dst, t_list *src);

/*
**	SRC/FT_LIST_CREATE.C
*/

t_list						*list_create(void *content);

/*
**	SRC/FT_LIST_DELETE.C
*/

int							ft_list_del_until(t_list **list,
												int (*assert)(void *),
												void (*ptr_free)(void **));
void						ft_list_delete(t_list **elem,
											void (*ptr_free)(void **));
void						ft_list_clear(t_list **list,
											void (*ptr_free)(void **));

/*
**	SRC/FT_LIST_FOREACH.C
*/

void						list_foreach(t_list *head, void (*iter)());
void						list_foreach_if(t_list *head, void (*iter)(),
											int (*test)());

void						list_foreach_data(t_list *head, void (*iter)(),
												void *data);
void						list_foreach_if_data(t_list *head, void (*iter)(),
													int (*test)(), void *data);

/*
**	SRC/FT_LIST_SPLIT.C
*/

void						list_split(t_list **head, t_list **splitted,
										int (*assert)());
void						list_split_data(t_list **head, t_list **splitted,
											int (*assert)(), void *data);

/*
**	SRC/FT_LIST_LAST.C
*/

t_list						*ft_list_last(t_list *list);

/*
**	SRC/FT_LIST_INSERT.C
*/

void						ft_list_insert(t_list **head, t_list **curr,
											t_list *elem);

#endif
