/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qbuf_dump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:31:45 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/22 11:37:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qbuf.h"

char				*qbuf_dump(t_qbuf *buf)
{
	char			*ret;
	
	ret = ft_strdup(buf->buffer);
	ft_bzero(buf->buffer, buf->used);
	buf->used = 0;
	return (ret);
}
