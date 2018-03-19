/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_from_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 11:40:48 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 13:49:16 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"
#include "ft_string.h"

t_dlist	*dlst_from_str(char *str)
{
	t_dlist		*lst;
	unsigned	len;
	char		*buf;

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
