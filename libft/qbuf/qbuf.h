/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qbuf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 19:12:30 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/19 19:34:28 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QBUF_H
# define QBUF_H

# include <stdlib.h>
# include "ft_string.h"

typedef struct s_qbuf	t_qbuf;

struct					s_qbuf
{
	char				*buffer;
	size_t				used;
	size_t				size;
};

t_qbuf					*qbuf_new(size_t first);

int						qbuf_add(t_qbuf *buf, char *str);
int						qbuf_addn(t_qbuf *buf, char *str, size_t n);
int						qbuf_addc(t_qbuf *buf, char c);

int						qbuf_grow(t_qbuf *buf);
int						qbuf_grown(t_qbuf *buf, size_t n);

char					*qbuf_del(t_qbuf **buf);
void					qbuf_clear(t_qbuf *buf);

#endif
