/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strexpand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 16:59:37 by lportay           #+#    #+#             */
/*   Updated: 2017/08/26 16:59:38 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Renvoie une chaîne ou le premier caractere 'c' rencontré dans la chaine 'str'
** est remplacé par l'expression 'expr' si la chaine 'str' est non-valide ou que
** le caractere 'c' n'est pas trouvé ou non-imprimable, la fonction renvoie NULL
*/

char	*ft_strexpand(char *str, char c, char *expr)
{
	char		*tmp;
	char		*new_str;
	long int	diff;

	if (!str || !expr || ft_isprint(c) == 0 || (tmp = ft_strchr(str, c)) == NULL
		|| (new_str = ft_strnew(ft_strlen(str) + ft_strlen(expr) - 1)) == NULL)
		return (str);
	diff = tmp - str;
	ft_strncpy(new_str, str, diff);
	ft_strcpy(new_str + diff, expr);
	ft_strcpy(new_str + diff + ft_strlen(expr), str + diff + 1);
	return (new_str);
}
