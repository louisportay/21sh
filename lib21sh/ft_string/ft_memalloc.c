/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:22:40 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/10 18:06:46 by vbastion         ###   ########.fr       */
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

void		*ft_pmemalloc(size_t size, void (*on_error)(int), int status)
{
	void	*ret;

	if ((ret = malloc(size)) == NULL)
	{
		on_error(status);
		return (NULL);
	}
	ft_bzero(ret, size);
	return (ret);
}
