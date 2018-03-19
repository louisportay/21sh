/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:59:15 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/15 10:25:49 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				on_emem(int status)
{
	fatal_err((char)status, get_ctxaddr());
}

void				max(size_t *a, size_t b)
{
	if (*a < b)
		*a = b;
}

void				ft_assert(void ***arr, size_t len)
{
	size_t			i;
	int				err;

	i = 0;
	err = 0;
	while (i < len)
	{
		if (arr[i] == NULL)
			err = 1;
		i++;
	}
	if (err)
	{
		i = 0;
		while (i < len)
		{
			ft_memdel(arr[i]);
			i++;
		}
		on_emem(NOMEM);
	}
}
