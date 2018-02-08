/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 15:12:59 by lportay           #+#    #+#             */
/*   Updated: 2017/08/24 21:42:44 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** prev_c codes -- 0 = delimiter | 1 = char | 2 = opening \" | 3 = closing \"
*/

static void	str_nb(char const *s, int c, int *str_nb)
{
	int	prev_c;

	*str_nb = 0;
	prev_c = 0;
	while (*s)
	{
		if (*s == c && prev_c != 2)
			prev_c = 0;
		else if (*s == '\"' && prev_c == 2)
		{
			*str_nb += 1;
			prev_c = 3;
		}
		else if (*s == '\"')
			prev_c = 2;
		else if (prev_c == 0 || prev_c == 3)
		{
			*str_nb += 1;
			prev_c = 1;
		}
		s++;
	}
	if (prev_c == 2)
		*str_nb = -1;
}

static int	quotes(char const **s, char **str_tab)
{
	char	*tmp;
	int		len;

	tmp = (char *)++(*s);
	len = 0;
	while (**s && **s != '\"')
	{
		len++;
		(*s)++;
	}
	if (!((*str_tab) = (char *)malloc(sizeof(char) * len + 1)))
		return (-1);
	ft_strncpy(*str_tab, tmp, len);
	(*str_tab)[len] = '\0';
	(*s)++;
	return (0);
}

static int	delimiter(char const **s, char **str_tab, char c)
{
	char	*tmp;
	int		len;

	tmp = (char *)*s;
	len = 0;
	while (**s && **s != c && **s != '\"')
	{
		len++;
		(*s)++;
	}
	if (!((*str_tab) = (char *)malloc(sizeof(char) * len + 1)))
		return (-1);
	ft_strncpy(*str_tab, tmp, len);
	(*str_tab)[len] = '\0';
	return (0);
}

static int	split(char const *s, char **str_tab, char c)
{
	while (*s)
	{
		if (*s == '\"')
		{
			if (quotes(&s, str_tab++) == -1)
				return (-1);
		}
		else if (*s != c)
		{
			if (delimiter(&s, str_tab++, c) == -1)
				return (-1);
		}
		else if (*s == c)
			s++;
	}
	return (0);
}

char		**ft_strsplitquote(char const *s, char c)
{
	char	**str_tab;
	int		width;

	if (!s || ft_isprint(c) == 0 || ft_strlen(s) == 0 || ft_stroccur(s, c)
		== ft_strlen(s) || ft_stroccur(s, '\"') == ft_strlen(s))
		return (NULL);
	str_nb(s, c, &width);
	if (width == -1)
		return (NULL);
	if (!(str_tab = (char **)malloc(sizeof(char *) * (width + 1))))
		return (NULL);
	str_tab[width] = NULL;
	if (split(s, str_tab, c) == -1)
		return (NULL);
	return (str_tab);
}
