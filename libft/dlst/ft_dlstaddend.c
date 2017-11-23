/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstaddend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:33:01 by lportay           #+#    #+#             */
/*   Updated: 2017/11/17 17:25:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstaddend(t_dlist *alst, t_dlist *new)
{
	t_dlist		*tmp;

	tmp = alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->previous = tmp;
	new->next = NULL;
}
