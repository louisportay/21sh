/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_from_dlst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:26:11 by lportay           #+#    #+#             */
/*   Updated: 2018/04/09 11:07:44 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"

/*
** Take a double linked-list as only argument, and return a string consisting of
** the first letter stored in the 'data' field of each maillon
** Skip the 'HEAD' maillon
** This function is not protected
*/

char	*str_from_dlst(t_dlist *dlst)
{
	char	*s;
	int		len;

	if (!dlst)
		return (NULL);
	len = ft_dlstcount(dlst) + 1;
	if ((s = (char *)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	len = 0;
	dlst = dlst->next;
	while (dlst)
	{
		s[len++] = *((char *)dlst->data);
		dlst = dlst->next;
	}
	s[len] = '\0';
	return (s);
}
