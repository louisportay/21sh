/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_dlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 11:40:48 by lportay           #+#    #+#             */
/*   Updated: 2017/12/27 13:28:51 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*str_to_dlst(char *str)
{
	t_dlist 	*lst;
	unsigned	len;
	char 		*buf;

	if (!str)
		return (NULL);
	lst = NULL;
	len = ft_strlen(str);
	while (len--)
	{
		buf = (char *)malloc(sizeof(char) + 1);
		buf[0] = str[len];
		buf[1] = '\0';
		ft_dlstadd(&lst, ft_dlstnewaddr(buf, 1));
	}
	ft_dlstadd(&lst, ft_dlstnew("HEAD", 5));
	return (lst);
}
