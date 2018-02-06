/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 09:49:03 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 16:02:43 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Return a dynamically allocated string composed by dirname + '/' + basename
*/

char *fullpath(char *dirname, char *basename)
{
	char		*fullname;
	unsigned	len;

	if (!dirname)
		return (ft_strdup(basename));
 	if (!basename)
		return (ft_strdup(dirname));
	len = ft_strlen(dirname) + ft_strlen(basename) + 2;
	if (!(fullname = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ft_bzero(fullname, len);
	ft_strcat(fullname, dirname);
	ft_strcat(fullname, "/");
	ft_strcat(fullname, basename);
	return (fullname);
}
