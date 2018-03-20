/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qbuf_dump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:31:45 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/19 16:10:49 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qbuf.h"

char	*qbuf_dump(t_qbuf *buf)
{
	char			*ret;

	ret = ft_strdup(buf->buffer);
	ft_bzero(buf->buffer, buf->used);
	buf->used = 0;
	return (ret);
}
