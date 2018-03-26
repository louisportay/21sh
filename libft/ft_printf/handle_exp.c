/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:32:59 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/25 18:09:21 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			prepare_double(t_exp *e)
{
	int				neg;
	int				negpre;

	neg = e->d < 0;
	neg && (e->d = -(e->d));
	neg && (e->buf[e->len++] = '-');
	negpre = (e->d) < 1;
	if (negpre)
	{
		while ((e->d) < 1)
		{
			(e->sz)++;
			(e->d) *= 10;
		}
	}
	else
	{
		while ((e->d) > 10)
		{
			(e->sz)++;
			(e->d) /= 10;
		}
	}
}

static void			bufferize(t_exp *e, t_flag *flag)
{
	int				i;
	size_t			pre;

	pre = (flag->sz_flag & 6) ? flag->pre : 6;
	(e->rem) = pre > 49 ? pre - 49 : 0;
	pre = (e->rem) != 0 ? 49 : pre;
	i = (int)e->d;
	e->buf[e->len++] = i + '0';
	e->d -= i;
	e->buf[e->len++] = '.';
	e->d += rounder(pre + 1);
	while (pre > 0)
	{
		e->d *= 10;
		i = (int)e->d;
		e->buf[e->len++] = i + '0';
		e->d -= i;
		pre--;
	}
}

static u_char		get_spec(t_flag *flag, t_exp *e)
{
	return (((flag->flag & (1 << 10)) == 0)
			| (((flag->sz_flag & 1) && flag->min > e->len) << 1)
			| (((flag->flag & (1 << 12)) != 0) << 2)
			| (((flag->flag & (1 << 9)) != 0) << 3));
}

static void			endbuffering(t_exp *e, t_flag *flag, u_char *spec)
{
	e->buf[e->len++] = flag->c == 'e' ? 'e' : 'E';
	e->buf[e->len++] = e->negpre ? '-' : '+';
	e->buf[e->len++] = (e->sz > 9 ? e->sz / 10 : 0) + '0';
	e->buf[e->len++] = (e->sz % 10) + '0';
	if (e->rem == 0 && ((*spec) & 3) == 3)
	{
		(((*spec) & 12) == 12) && fpf_buf_addc('+');
		fpf_buf_addfillers(((*spec) & 8) == 0,
							flag->min - e->len - (((*spec) & 4) == 4));
		(((*spec) & 12) == 4) && fpf_buf_addc('+');
	}
	fpf_buf_add(e->buf, e->len);
	if ((*spec) == 2)
		fpf_buf_addfillers(1, (flag->min - e->len - e->rem
								- (e->rem != 0 ? 51 : 0)));
}

int					fpf_handle_exp(va_list *ap, t_flag *flag)
{
	u_char			spec;
	t_exp			e;

	e = (t_exp){ .buf = fpf_buf_get()->tmp_buf, .len = 0, .sz = 0 };
	ft_bzero(e.buf, FT_TMPBSZ);
	e.d = va_arg(*ap, double);
	e.negpre = (e.d > 0 && e.d < 1) || (e.d < 0 && e.d > -1);
	prepare_double(&e);
	bufferize(&e, flag);
	spec = get_spec(flag, &e);
	if (e.rem != 0)
	{
		if ((spec & 3) == 3)
		{
			((spec & 12) == 12) && fpf_buf_addc('+');
			fpf_buf_addfillers((spec & 8) == 0,
								flag->min - e.rem - 55 - ((spec & 4) == 4));
			((spec & 12) == 4) && fpf_buf_addc('+');
		}
		fpf_buf_add(e.buf, e.len);
		fpf_buf_addfillers(0, e.rem);
		e.len = 0;
	}
	endbuffering(&e, flag, &spec);
	return (1);
}
