/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabtolst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 14:53:22 by lportay           #+#    #+#             */
/*   Updated: 2017/10/04 19:57:09 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_tabtolst(char **tab)
{
	t_list *lst;

	if (tab == NULL)
		return (NULL);
	lst = ft_lstnew(*tab, (*tab == NULL) ? 0 : ft_strlen(*tab));
	tab++;
	while (*tab)
	{
		ft_lstaddend(&lst, ft_lstnew(*tab, ft_strlen(*tab)));
		tab++;
	}
	return (lst);
}
