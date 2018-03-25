/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 16:47:01 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/25 20:39:48 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_matching.h"
#include "dir_explorer.h"

static int		multi_expand(t_list *lst)
{
	char		*s;
	int			ret;

	while (lst != NULL)
	{
		s = (char *)lst->content;
		if ((ret = do_expand_glob(&s)) < 1)
		{
			ft_list_clear(&lst, &ft_memdel);	//faut lui passer l'adresse, parce que la il met personne a NULL
			return (ret);
		}
		lst->content = (void *)s;
		lst = lst->next;
	}
	return (1);
}

static char		*bufferize(t_list *lst)
{
	t_qbuf		*buf;

	buf = qbuf_new(128);
	while (lst != NULL)
	{
		qbuf_add(buf, (char *)lst->content);
		lst = lst->next;
		if (lst != NULL)
			qbuf_addc(buf, ' ');
	}
	return (qbuf_del(&buf));
}

int				expand_glob(char **str, t_ctx *ctx)
{
	t_list		*lst;
	int			ret;

	if (ctx->set & BU_SET_FNEXP)
		return (1);
	if (str == NULL || *str == NULL || **str == '\0')
		return (1);
	lst = bridge_strsplit(*str);
	if ((ret = multi_expand(lst)) < 1)
	{
		if (ret == -1)
			return (ret);
		if (ctx->set & FAILGLOB)
			return (-2);
		else if (ctx->set & NULLGLOB)
			return (-3);
		return (0);
	}
	ft_strdel(str);
	*str = bufferize(lst);
	ft_list_clear(&lst, &ft_memdel);
	return (*str != NULL ? 1 : -1);
}
