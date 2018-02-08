/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 20:24:29 by lportay           #+#    #+#             */
/*   Updated: 2018/01/17 10:59:06 by lportay          ###   ########.fr       */
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

	while (alst)
	{
		tmp = alst->next;
		(*del)(alst->content, tmp->content_size);
		free(alst);
		alst = tmp;
	}
}

static void	lstdel_maillon(t_list *alst)
{
	t_list *tmp;

	while (alst)
	{
		tmp = alst->next;
		free(alst);
		alst = tmp;
	}
}

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (del)
		lstdel_content(*alst, del);
	else
		lstdel_maillon(*alst);
	*alst = NULL;
}
