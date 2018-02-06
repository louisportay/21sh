/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:22:40 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 16:06:35 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void		*ft_memalloc(size_t size)
{
	void	*ret;

	if ((ret = malloc(size)) == NULL)
		return (NULL);
	ft_bzero(ret, size);
	return (ret);
}

void		*ft_memalloc_err(size_t size, int (*on_error)(int), int status)
{
	void	*ret;

	if ((ret = malloc(size)) == NULL)
		return ((void *)(on_error(status) * 0ll));
	ft_bzero(ret, size);
	return (ret);
}
