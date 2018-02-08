/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 20:16:16 by lportay           #+#    #+#             */
/*   Updated: 2017/10/25 19:03:04 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Cette fonction détruit un seul maillon elle ne doit donc pas être utilisé
** sur le début  d'une liste au risque de perdre tous les maillons suivants.
** l'utilisation de ft_lstremove est plus haut niveau et est préférable
** (restore les liens des maillons entre eux après suppression du maillon)
*/

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	(*del)((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
