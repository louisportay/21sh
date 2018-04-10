/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 18:21:54 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 16:25:41 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static u_char		get_spec(char *str, t_flag *flag)
{
	u_char		spec;

	spec = 0;
	spec |= (fpf_strchr("dDi", flag->c) != NULL) << 5;
	spec |= (fpf_strcmp("0", str) != 0) << 6;
	spec |= ((spec & (1 << 5)) && str[0] == '-' && (flag->flag & (1 << 9)));
	spec |= (((flag->flag & (1 << 8)) != 0) && (spec & (1 << 6))
				&& (fpf_strchr("oO", flag->c) != 0)) << 1;
	spec |= ((flag->flag & (1 << 8)) != 0 && (spec & (1 << 6))
				&& fpf_strchr("xX", flag->c) != 0) << 2;
	spec |= (((flag->flag & (1 << 12)) != 0 && str[0] != '-'
				&& (spec & (1 << 5))) << 3);
	spec |= (((flag->flag & 0x1800) == 0x0800 && str[0] != '-'
				&& (spec & (1 << 5))) << 4);
	return (spec);
}

static u_char		get_specpreci(t_flag *flag, char **str)
{
	u_char			spec;

	spec = (*str)[0] == '-';
	spec |= (fpf_strchr("oO", flag->c) != NULL
				&& (flag->flag & (1 << 8)) != 0) << 1;
	spec |= ((spec & (1 << 1)) && (*str)[0] != '0') << 2;
	spec |= (fpf_strchr("xX", flag->c) != NULL && (flag->flag & (1 << 8))) << 3;
	spec |= (((flag->flag & (1 << 12)) != 0
				&& fpf_strchr("dDi", flag->c) != NULL) << 4);
	return (spec);
}

static void			handle_pre_rem(char **str, t_flag *flag, size_t *len,
									u_char spec)
{
	if (spec & 1)
	{
		fpf_buf_addc('-');
		(*str)++;
		(*len)--;
	}
	if ((spec & 17) == 16)
		fpf_buf_addc('+');
	if (flag->pre > (*len + ((spec & (1 << 2)) != 0)))
		fpf_buf_addfillers(0, flag->pre - (*len + ((spec & (1 << 2)) != 0)));
	if (spec & (1 << 1))
		fpf_buf_addc('0');
}

int					fpf_handle_pre(char **str, t_flag *flag, size_t *len)
{
	u_char		spec;
	size_t		biggest;
	size_t		tmp;

	spec = get_specpreci(flag, str);
	if ((flag->sz_flag & 4) != 0 && flag->pre == 0 && (*str)[0] == '0')
		return (((spec & (1 << 1)) && fpf_buf_addc('0')) * 0);
	biggest = (flag->pre > *len) ? flag->pre : *len;
	if (spec & (1 << 3))
		fpf_buf_add(flag->c == 'x' ? "0x" : "0X", 2);
	if ((flag->sz_flag & 1) && flag->min > biggest
			&& !(flag->flag & (1 << 10)))
	{
		tmp = flag->pre + ((spec & 1) != 0) + ((spec & (1 << 4)) != 0);
		if ((flag->sz_flag & 1) && (tmp != flag->min))
			fpf_buf_addfillers(1, flag->min - biggest
									- (((spec & 1) && flag->pre > *len))
									- (((spec & (1 << 4)) != 0)));
	}
	handle_pre_rem(str, flag, len, spec);
	return (1);
}

void				fpf_strwithsize(char *str, t_flag *flag)
{
	int			pre;
	size_t		len;
	u_char		spec;
	size_t		written;

	written = fpf_buf_gettotal(NULL);
	len = fpf_strlen(str);
	pre = ((flag->sz_flag & 2) != 0 && flag->pre < len) ? flag->pre : len;
	spec = get_spec(str, flag);
	if ((flag->sz_flag & 2) != 0)
	{
		if (fpf_handle_pre(&str, flag, &len) == 0)
		{
			if (flag->sz_flag & 1)
				fpf_buf_addfillers(1, flag->min);
			pad_after(flag, 0);
			return ;
		}
	}
	else
		fpf_handle_prefix(flag, spec, len);
	fpf_buf_add(str + ((spec & 1) && !(flag->sz_flag & 6)),
			((fpf_strchr("dDiuUoOxXp", flag->c)) ? len : (size_t)pre)
				- ((spec & 1) && !(flag->sz_flag & 6)));
	pad_after(flag, fpf_buf_gettotal(NULL) - written);
}
