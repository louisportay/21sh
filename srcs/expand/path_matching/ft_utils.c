/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:53:53 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/07 15:54:41 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pattern_matching.h"

void			ft_mb_add_unsafe(t_membuf *buf, char *str)
{
	while (*str != '\0')
		ft_mb_addc(buf, *(str++));
}

void			ft_mb_pushrange(t_membuf *buf, char beg, char end)
{
	while (beg <= end)
	{
		ft_mb_addc(buf, beg);
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

char			*ft_strrmdup(char **str)
{
	char		*s;
	u_char		c;
	int			mod;
	t_membuf	buf;
	char		prz[UCHAR_MAX];

	s = *str;
	mod = 0;
	ft_bzero(prz, SCHAR_MAX);
	ft_mb_init(&buf);
	while (*s != '\0')
	{
		c = *(s++);
		if (prz[c] == 0)
			ft_mb_addc(&buf, c);
		else
			mod = 1;
		prz[c] = 1;
	}
	if (mod)
	{
		ft_strdel(str);
		*str = ft_mb_fetch(&buf);
	}
	return (*str);
}
