/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_from_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 11:40:48 by lportay           #+#    #+#             */
/*   Updated: 2018/04/09 12:57:38 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"
#include "ft_string.h"

static void	*del_list_return_null(t_dlist **lst)
{
	ft_dlstdel(lst, &delvoid);
	return (NULL);
}

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
		if ((buf = (char *)malloc(sizeof(char) + 1)) == NULL)
			return (del_list_return_null(&lst));
		buf[0] = str[len];
		buf[1] = '\0';
		if (ft_dlstnewadd(&lst, buf, 1, &ft_dlstnewaddr) == -1)
			return (del_list_return_null(&lst));
	}
	if (ft_dlstnewadd(&lst, "HEAD", 5, &ft_dlstnew) == -1)
		return (del_list_return_null(&lst));
	return (lst);
}
