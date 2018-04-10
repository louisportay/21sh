/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:15:25 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 16:17:14 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		conv_precision(const char *str, size_t *i,
											t_flag *flag)
{
	if ((flag->sz_flag & 4) != 0)
	{
		flag->pre = ft_atoi(str + *i);
		flag->sz_flag |= 2;
	}
	else
	{
		flag->min = ft_atoi(str + *i);
		flag->sz_flag |= 1;
	}
	while (fpf_isnum(str[*i]))
		(*i)++;
}

static int		conv_typeflag(const char *str, size_t *i, t_flag *flag)
{
	size_t		pos;
	size_t		len;
	const char	**flags = (const char *[6]) { "hh", "h", "ll", "l", "j", "z" };
	u_char		fl;

	pos = 0;
	while (pos != 6)
	{
		len = fpf_strlen(flags[pos]);
		if (fpf_strncmp(flags[pos], str + *i, len) == 0)
		{
			if ((fl = (flag->flag & 0xFF)) == 0)
				flag->flag |= 1 << pos;
			else if ((fl == 1 && pos > 0) || (fl == 2 && pos > 1))
				flag->flag = (flag->flag & 0xFF00) | 1 << pos;
			(*i) += len;
			return (1);
		}
		pos++;
	}
	return (0);
}

static int		conv_flagflag(char c, t_flag *flag)
{
	int			i;

	i = 0;
	while (FPF_FLAG[i] != '\0')
	{
		if (FPF_FLAG[i] == c)
		{
			if (c == '0' && (flag->sz_flag & 4) == 0)
				flag->sz_flag |= (1 << 7);
			flag->flag |= 1 << (i + 8);
			return (1);
		}
		i++;
	}
	return (0);
}

static int		conv_iswildcard(const char *str, size_t *i, va_list *ap,
								t_flag *flag)
{
	int			sz;

	if (str[*i] != '*')
		return (0);
	(*i)++;
	sz = va_arg(*ap, int);
	if ((flag->sz_flag & 4) != 0)
	{
		if (sz >= 0 || (sz < 0 && flag->sz_flag & 1))
		{
			flag->sz_flag |= 2;
			flag->pre = (sz >= 0) ? (size_t)sz : flag->min;
		}
		else
			flag->sz_flag = 0;
	}
	else
	{
		flag->sz_flag |= 1;
		flag->min = sz < 0 ? -sz : sz;
		if (sz < 0)
			flag->flag |= (1 << 10);
	}
	return (1);
}

int				flag_get(const char *str, size_t *i, va_list ap,
							t_flag *flag)
{
	if (conv_flagflag(str[*i], flag))
		(*i)++;
	else if (str[*i] != '0' && fpf_isnum(str[*i]))
		conv_precision(str, i, flag);
	else if (str[*i] == '.')
	{
		flag->sz_flag |= 4;
		(*i)++;
	}
	else if (str[*i] == '*')
		conv_iswildcard(str, i, (va_list *)ap, flag);
	else if (conv_typeflag(str, i, flag))
		;
	else
		return (0);
	return (1);
}
