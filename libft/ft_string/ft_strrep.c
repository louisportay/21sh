/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 15:36:50 by lportay           #+#    #+#             */
/*   Updated: 2017/05/10 15:54:29 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Delete the old string in str and replace it with a pointer (new_str)
*/

void	ft_strrep(char **str, char *new_str)
{
	ft_strdel(str);
	*str = new_str;
}
