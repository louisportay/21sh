/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:53:53 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 14:20:29 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pattern_matching.h"

void			qbuf_addrange(t_qbuf *buf, char beg, char end)
{
	while (beg <= end)
	{
		qbuf_addc(buf, beg);
		beg++;
	}
}

int				ft_strwildcmp(char *str, char *matcher)
{
	while (*str != '\0' && *matcher != '\0')
	{
		if (*matcher == '*' || *str == *matcher)
		{
			str++;
			matcher++;
		}
		else
			return (*str - *matcher);
	}
	return (*matcher == '\0' ? 0 : (*str - *matcher));
}

static char		*lcleanup(int mod, char **str, t_qbuf **buf)
{
	if (mod)
	{
		ft_strdel(str);
		*str = qbuf_del(buf);
	}
	else
		qbuf_nuke(buf);
	return (*str);
}

char			*ft_strrmdup(char **str)
{
	char		*s;
	u_char		c;
	int			mod;
	t_qbuf		*buf;
	char		prz[UCHAR_MAX];

	s = *str;
	mod = 0;
	ft_bzero(prz, UCHAR_MAX);
	buf = qbuf_new(1 << 8);
	while (*s != '\0')
	{
		c = *(s++);
		if (c >= UCHAR_MAX)
			continue ;
		if (c < UCHAR_MAX && prz[c] == 0)
			qbuf_addc(buf, c);
		else
			mod = 1;
		prz[c] = 1;
	}
	return (lcleanup(mod, str, &buf));
}
