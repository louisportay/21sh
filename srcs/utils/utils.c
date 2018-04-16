/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:59:15 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 17:02:20 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

int					print_err(char *msg, int ret)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (ret);
}

size_t				ft_read(int fd, char *buffer, size_t size)
{
	size_t				ret;
	size_t				total;

	total = 0;
	while (size)
	{
		if ((ret = read(fd, buffer + total, size)) == (size_t)-1)
		{
			ft_dprintf(STDERR_FILENO,
						"Critical error in ft_read. FD or buffer error\n");
			return ((size_t)-1);
		}
		total += ret;
		size -= ret;
	}
	return (total);
}
