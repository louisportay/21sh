/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:53:15 by lportay           #+#    #+#             */
/*   Updated: 2017/12/05 12:18:21 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DLST_H
# define FT_DLST_H

/*
** Every list created with this set of functions should have a 'HEAD' maillon
*/

typedef struct		s_dlist
{
	void			*content;
	size_t			content_size;
	struct s_dlist	*previous;
	struct s_dlist	*next;
}					t_dlist;

t_dlist				*ft_dlstnew(void const *content, size_t content_size);
t_dlist				*ft_dlstnewaddr(void const *content, size_t content_size);
void				ft_dlstadd(t_dlist **alst, t_dlist *new);
void				ft_dlstaddend(t_dlist *alst, t_dlist *new);
void				ft_dlstdel(t_dlist **alst, void (*del)(void *, size_t));
void				ft_dlstremove(t_dlist **alst, void (*del)(void *, size_t));
void				ft_dlstdelone(t_dlist **alst, void (*del)(void *, size_t));
void				ft_dlsthead(t_dlist **dlst);
void				ft_dlstend(t_dlist **dlst);
size_t				ft_dlstcount(t_dlist *dlst);
size_t				ft_dlstindex(t_dlist *dlst);
t_dlist				*ft_dlstaddr(t_dlist *dlst, size_t rank);
void				ft_dlstprint(t_dlist *list, char *separator);
void				ft_dlstinsert(t_dlist *previous, t_dlist *between);
t_dlist				*str_to_dlst(char *str);
char				*dlst_to_str(t_dlist *dlst);
t_dlist				*ft_dlstdup(t_dlist *dlst);

#endif
