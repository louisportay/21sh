/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_prepend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 16:21:46 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/17 16:24:11 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void						list_prepend(t_list **dst, t_list *src)
{
	t_list *tmp;

	while (src != NULL)
	{
		tmp = src->next;
		src->next = *dst;
		*dst = src;
		src = tmp;
	}
}
