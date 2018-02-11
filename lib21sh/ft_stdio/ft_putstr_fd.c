/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:56:50 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/11 15:26:36 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

void		ft_putstr_fd(char const *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}

void		ft_putstr(char const *s)
{
	if (s == NULL)
		return ;
	write(STDOUT_FILENO, s, ft_strlen(s));
}

void		ft_putendl(char const *s)
{
	if (s == NULL)
		return ;
	write(STDOUT_FILENO, s, ft_strlen(s));
	write(STDOUT_FILENO, "\n", 1);
}

void		ft_putendl_fd(char const *s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
