/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putc_in_buf_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:08:55 by lportay           #+#    #+#             */
/*   Updated: 2017/10/13 16:53:20 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Insert the character 'a' in the buffer 'buf', add 1 to i and print to the buffer
** to 'fd' if it's full
*/

void	putc_in_buf_fd(int fd, char a, char *buf, size_t *i)
{
	buf[(*i)++ % BUFF_SIZE] = a;
	if ((*i % BUFF_SIZE) == 0 && *i != 0)
		write(fd, buf, BUFF_SIZE);
}
