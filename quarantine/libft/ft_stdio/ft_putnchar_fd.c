/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 16:57:11 by lportay           #+#    #+#             */
/*   Updated: 2017/10/19 16:55:50 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Print 'n' times the char 'c' on 'fd'
*/

void	ft_putnchar_fd(int fd, char c, size_t n)
{
	size_t	i;
	char	buf[BUFF_SIZE];

	i = 0;
	while (i < n)
		putc_in_buf_fd(fd, c, buf, &i);
	write(fd, &buf, i % BUFF_SIZE);
}
