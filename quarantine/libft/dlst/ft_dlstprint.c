/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 10:58:56 by lportay           #+#    #+#             */
/*   Updated: 2017/11/17 17:41:26 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstprint(t_dlist *list, char *separator)
{
	while (list)
	{
		ft_putstr(list->content);
		ft_putstr(separator);
		list = list->next;
	}
}
