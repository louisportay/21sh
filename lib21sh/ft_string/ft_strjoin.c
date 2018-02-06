/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:30:13 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/09 19:11:36 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*ret;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	if (s1 != NULL && s2 == NULL)
		return (ft_strdup(s1));
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if ((ret = ft_strnew(l1 + l2)) == NULL)
		return (NULL);
	ft_strncpy(ret, s1, l1);
	ft_strncpy(ret + l1, s2, l2);
	return (ret);
}

char		*ft_strjoinc(char const *s1, char const *s2, char const c)
{
	size_t	l1;
	size_t	l2;
	char	*ret;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	if (s1 != NULL && s2 == NULL)
		return (ft_strdup(s1));
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if ((ret = ft_strnew(l1 + l2 + 1)) == NULL)
		return (NULL);
	ft_strncpy(ret, s1, l1);
	ret[l1] = c;
	ft_strncpy(ret + l1 + 1, s2, l2);
	return (ret);
}

char		*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	size_t	len;
	char	*ret;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL && s2 != NULL)
		return (ft_strndup(s2, n));
	if (s1 != NULL && s2 == NULL)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	if ((ret = ft_strnew(len + n)) == NULL)
		return (NULL);
	ft_strncpy(ret, s1, len);
	ft_strncpy(ret + len, s2, n);
	return (ret);
}
