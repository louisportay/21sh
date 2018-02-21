/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:53:38 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/21 18:22:42 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int						blt_output(t_proc *p)
{
	t_list				*lst;
	char				*str;
	(void)str;//

	if (p->type == BU_STR)
	{
		if (p->data.str != NULL)
			ft_putstr_fd(p->data.str + 1, p->data.str[0] - '0');
		return (p->status);
	}
	lst = p->data.out;
	while (lst != NULL)
	{
		str = (char *)lst->content;
		ft_putstr_fd((char *)lst->content + 1, ((char *)lst->content)[0] - '0');
		lst = lst->next;
	}
	return (p->status);
}
