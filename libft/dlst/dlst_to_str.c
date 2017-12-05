/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:26:11 by lportay           #+#    #+#             */
/*   Updated: 2017/12/02 13:30:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Take a double linked-list as only argument, and return a string consisting of
** the first letter stored in the 'content' field of each maillon
** Skip the 'HEAD' maillon
*/

char	*dlst_to_str(t_dlist *dlst)
{
	char *s;
	int len;

	if (!dlst->next)
		return (NULL);
	len = ft_dlstcount(dlst) + 1;
	s = (char *)malloc(sizeof(char) * len);
	len = 0;
	dlst = dlst->next;
	while (dlst)
	{
		s[len++] = *((char *)dlst->content);
		dlst = dlst->next;
	}
	s[len] = '\0';
	return (s);
}
