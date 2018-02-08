/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:52:21 by lportay           #+#    #+#             */
/*   Updated: 2018/01/15 22:31:14 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LST_H
# define FT_LST_H

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstaddend(t_list **alst, t_list *new);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstinsert(t_list **alst, size_t rank, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstmove(t_list **alst, size_t rank, size_t new_rank);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstprint(t_list *list);
void			ft_lstremove(t_list **alst, size_t rank, void (*del)(void *,
			size_t));
size_t			ft_lstcount(t_list *lst);
size_t			ft_lstindex(t_list *lst, t_list *maillon);
t_list			*ft_lstaddr(t_list *lst, int n);
t_list			*ft_lstend(t_list *lst);
void			ft_lstmerge(t_list *lst1, t_list *lst2);
t_list			*ft_tabtolst(char **tab);
t_list			*ft_lstnewaddr(void const *content, size_t content_size);

#endif
