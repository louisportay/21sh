/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 16:57:11 by lportay           #+#    #+#             */
/*   Updated: 2017/10/11 17:13:37 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnchar(char c, size_t n)
{
	size_t	i;
	char	buf[BUFF_SIZE];

	i = 0;
	while (i < n)
		putc_in_buf(c, buf, &i);
	write(STDOUT_FILENO, &buf, i % BUFF_SIZE);
}
