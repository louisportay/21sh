/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 16:09:11 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/08 13:05:13 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		flag_isend(char c, t_flag *flag)
{
	int			i;

	i = 0;
	while (FPF_CONV[i] != '\0')
	{
		if (FPF_CONV[i] == c)
		{
			flag->id = i;
			flag->c = c;
			return (1);
		}
		i++;
	}
	return (0);
}

int				fpf_flag_print(const char *str, size_t *i, t_flag *flag,
								va_list ap)
{
	t_handler	handler;

	if (str[*i] == '\0')
		return (0);
	if (flag_isend(str[*i], flag)
		&& (((handler = fpf_ptrget(flag->id)) != NULL) | ((*i)++) | 1))
		return (handler((va_list *)ap, flag));
	else
	{
		pad_before(flag, 1);
		fpf_buf_addc(str[*i]);
		pad_after(flag, 1);
	}
	(*i)++;
	return (1);
}
