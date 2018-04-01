/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 15:59:40 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 12:31:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_quotes.h"

static void			push_str_til(char **str, t_qbuf *buf, char c)
{
	char			*s;

	s = *str + 1;
	while (*s != c)
	{
		if (*s == '\\' && c == '\"' && *(s + 1) == '\"')
			s++;
		qbuf_addc(buf, *s);
		s++;
	}
	*str = s + 1;
}

static int			do_expand_quotes(char *str, char **ret)
{
	t_qbuf			*buf;

	buf = qbuf_new(1 << 8);
	while (*str != '\0')
	{
		if (*str == '\\')
		{
			str++;
			qbuf_addc(buf, *str);
			str++;
		}
		else if (*str == '\'')
			push_str_til(&str, buf, '\'');
		else if (*str == '\"')
			push_str_til(&str, buf, '\"');
		else
			qbuf_addc(buf, *(str++));
	}
	*ret = qbuf_del(&buf);
	return (*ret != NULL);
}

int					expand_quotes(t_list *list)
{
	char			*str;
	char			*tmp;

	while (list != NULL)
	{
		str = (char *)list->content;
		if (do_expand_quotes(str, &tmp) == 0)
		{
			ft_list_clear(&list, &ft_memdel);
			return (-1);
		}
		else
		{
			ft_strdel(&str);
			list->content = tmp;
		}
		list = list->next;
	}
	return (1);
}
