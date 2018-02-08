/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putc_in_buf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:08:55 by lportay           #+#    #+#             */
/*   Updated: 2017/10/11 17:04:26 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Insert the character 'a' in the buffer 'buf', add 1 to i and print the buffer
** if it's full
*/

void	putc_in_buf(char a, char *buf, size_t *i)
{
	buf[(*i)++ % BUFF_SIZE] = a;
	if ((*i % BUFF_SIZE) == 0 && *i != 0)
		write(STDOUT_FILENO, buf, BUFF_SIZE);
}
