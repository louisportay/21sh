/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 20:24:29 by lportay           #+#    #+#             */
/*   Updated: 2018/01/16 14:58:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Destroy in a safe way the whole list
** if del == NULL , no function will free the 'content' field
*/

static void	lstdel_content(t_list *alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	tmp = alst;
	while (tmp)
	{
		alst = alst->next;
		(*del)(tmp->content, tmp->content_size);
		free(tmp);
		tmp = alst;
	}
}

static void	lstdel_maillon(t_list *alst)
{
	t_list *tmp;

	tmp = alst;
	while (tmp)
	{
		alst = alst->next;
		free(tmp);
		tmp = alst;
	}
}

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (del)
		lstdel_content(*alst, del);
	else
		lstdel_maillon(*alst);
	free(*alst);
	*alst = NULL;
}
